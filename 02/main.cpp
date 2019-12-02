#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::atoi;
using std::vector;

int main() {

    ifstream input_file("../input.txt");
    vector<int> opcodes;

    for (int i; input_file >> i;) {
        opcodes.push_back(i);
        if (input_file.peek() == ',')
            input_file.ignore();
    }


    for (size_t i = 0; i < opcodes.size(); i++)
        cout << opcodes[i] << endl;

    int acc = 0;

    switch(opcodes.at(acc))
    {
        case 1:

            break;
        case 2:

            break;
        case 99:

            break;
        default:
            cout << "Something went wrong" << endl;
    }

    return 0;
}

