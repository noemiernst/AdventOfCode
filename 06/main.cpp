#include <iostream>
#include "node.h"
#include <fstream>
#include <map>
#include <queue>
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
            object_ptr->parent = mass_ptr;
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

vector<node*> path_to_root(node* start, node* root)
{
    node * it = start->parent;
    vector<node*> path;
    while(it != nullptr)
    {
        path.push_back(it);
        it = it->parent;
    }
    return path;
}

int find_distance(vector<node*> path1, vector<node*> path2)
{
    node* last = nullptr;
    while(path1.back() == path2.back())
    {
        last = path1.back();
        path1.pop_back();
        path2.pop_back();
    }
    return path1.size() + path2.size();
}

int main() {
    map<string, node*> nodes = read_map();

    node* root = find_root(nodes);

    cout << "Total orbits: " << root->total_orbits() << endl;

    int transfers = find_distance(path_to_root(nodes.find("YOU")->second, root), path_to_root(nodes.find("SAN")->second, root));

    cout << "Transfers: " << transfers << endl;

    return 0;
}
