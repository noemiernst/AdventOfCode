#include <iostream>
#include "node.h"
#include <fstream>
#include <map>
using namespace std;

map<string, node*> read_map()
{
    map<string, node*> nodes;
    string mass; //parent
    node* mass_ptr;
    string object; //child
    node* object_ptr;

    ifstream data("../input.txt");
    if(data.is_open())
    {
        while(getline(data, mass, ')'))
        {
            getline(data, object);
            if(nodes.find(mass) == nodes.end()) //not found
            {
                mass_ptr = new node(mass);
                nodes[mass] = mass_ptr;
            } else //found
            {
                mass_ptr = nodes.at(mass);
            }
            if(nodes.find(object) == nodes.end()) //not found
            {
                object_ptr = new node(object);
                nodes[object] = object_ptr;
            } else //found
            {
                object_ptr = nodes.at(object);
            }
            mass_ptr->children.push_back(object_ptr);
        }
    } else
        cout << "Could not open file" << endl;
    return nodes;
}

node * find_root(map<string, node*> nodes, node* root = nullptr, bool found = false)
{
    if(found)
        return root;
    node* root_start = root;
    if(root == nullptr)
        root = nodes.begin()->second;
    for (auto const& entry : nodes)
    {
        if(entry.second->is_child(root))
            root = entry.second;
    }
    if(root == root_start)
        found = true;
    return find_root(nodes, root, found);
}

int main() {
    map<string, node*> nodes = read_map();

    node* root = find_root(nodes);

    cout << "root: " << root->name << endl;
    for(auto node: nodes)
        cout << node.first << endl;

    cout << root->direct_orbits() << endl;
    cout << root->indirect_orbits() << endl;
    cout << root->total_orbits();

    return 0;
}
