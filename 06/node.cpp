//
// Created by Noemi Ernst on 06.12.19.
//

#include "node.h"
#include <iostream>
using std::cout;
using std::endl;

node::node(string name): name(name), parent(nullptr)
{ }

int node::direct_orbits()
{
    return children.size();
}

int node::indirect_orbits()
{
    int sum = 0;
    for (int i = 0; i < children.size(); ++i) {
        sum += children[i]->direct_orbits() + children[i]->indirect_orbits();
    }
    return sum;
}

int node::total_orbits()
{
    int sum = direct_orbits() + indirect_orbits();
    for(auto child: children)
    {
        sum += child->total_orbits();
    }
    return sum;
}

bool node::is_child(class node * child)
{
    for(auto c: children)
        if(c == child)
            return true;
    return false;
}

void node::display()
{
    cout << name << "  ";
    for(auto c: children)
    {
        c->display();
    }
}

int node::distance_to_child(node * child)
{
    node* it = this;
    while(it != child)
    {

    }
}