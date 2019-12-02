#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::atoi;
using std::vector;
using std::to_string;

int main() {

    ifstream input_file("../input.txt");
    vector<int> opcodes;

    for (int i; input_file >> i;) {
        opcodes.push_back(i);
        if (input_file.peek() == ',')
            input_file.ignore();
    }
    input_file.close();

    for (size_t i = 0; i < opcodes.size(); i++)
        cout << opcodes[i] << endl;

    int acc = 0;

    while(acc < opcodes.size())
    {
        switch(opcodes.at(acc))
        {
            case 1:
                opcodes.at(opcodes.at(acc+3)) = opcodes.at(opcodes.at(acc+1)) + opcodes.at(opcodes.at(acc+2));
                acc += 4;
                break;
            case 2:
                opcodes.at(opcodes.at(acc+3)) = opcodes.at(opcodes.at(acc+1)) * opcodes.at(opcodes.at(acc+2));
                acc += 4;
                break;
            case 99:
                cout << "Program finished with code 99" << endl;
                acc = opcodes.size();
                break;
            default:
                cout << "Something went wrong" << endl;
                acc = opcodes.size();
                break;
        }

    }

    ofstream output_file("../output.txt");
    output_file.clear();

    string solution;
    for (size_t i = 0; i < opcodes.size(); i++)
        solution += to_string(opcodes[i]) + ',';
    solution.pop_back();
    cout << solution;
    output_file << solution;

    output_file.close();

    return 0;
}

