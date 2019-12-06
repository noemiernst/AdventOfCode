//
// Created by Noemi Ernst on 06.12.19.
//

#ifndef INC_06_NODE_H
#define INC_06_NODE_H

#include <vector>
#include <string>
using std::vector;
using std::string;

class node {
public:
    string name;
    node * parent;
    vector<node *> children;

    node(string name);

    int direct_orbits();
    int indirect_orbits();
    int total_orbits();
    bool is_child(node* child);
    void display();
    int distance_to_child(node* child);

};


#endif //INC_06_NODE_H
