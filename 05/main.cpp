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
using std::cin;

vector<int> get_modes(int opcode)
{
    vector<int> instruction;
    instruction.push_back(opcode % 100);
    opcode /= 100;
    instruction.push_back(opcode % 10);
    opcode /= 10;
    instruction.push_back(opcode % 10);
    opcode /= 10;
    instruction.push_back(opcode % 10);

    return instruction;
}


int program(vector<int> opcodes)
{

    int acc = 0;
    int p1 = 0;
    int p2 = 0;

    while(acc < opcodes.size())
    {
        vector<int> instruction = get_modes(opcodes.at(acc));
        int res = 0;

        switch(instruction.at(0))
        {
            case 1:
                p1 = opcodes.at(acc+1);
                p2 = opcodes.at(acc+2);
                if(instruction.at(1) == 0)
                    p1 = opcodes.at(p1);
                if(instruction.at(2) == 0)
                    p2 = opcodes.at(p2);
                if(instruction.at(3) == 0)
                    opcodes.at(opcodes.at(acc+3)) = p1 + p2;
                else
                    opcodes.at(acc+3) = p1 + p2;
                acc += 4;
                break;
            case 2:
                p1 = opcodes.at(acc+1);
                p2 = opcodes.at(acc+2);
                if(instruction.at(1) == 0)
                    p1 = opcodes.at(p1);
                if(instruction.at(2) == 0)
                    p2 = opcodes.at(p2);
                if(instruction.at(3) == 0)
                    opcodes.at(opcodes.at(acc+3)) = p1 * p2;
                else
                    opcodes.at(acc+3) = p1 * p2;
                acc += 4;
                break;
            case 3:
                p1 = opcodes.at(acc+1);
                if(instruction.at(1) == 0)
                    p1 = opcodes.at(p1);
                int input;
                cout << "Enter Code: ";
                cin >> input;
                if(instruction.at(1) == 0)
                    opcodes.at(opcodes.at(acc+1)) = input;
                else
                    opcodes.at(acc+1) = input;
                acc += 2;
                break;
            case 4:
                p1 = opcodes.at(acc+1);
                if(instruction.at(1) == 0)
                    p1 = opcodes.at(p1);
                cout << "Output: " << p1 << endl;
                acc += 2;
                break;
            case 5:
                p1 = opcodes.at(acc+1);
                p2 = opcodes.at(acc+2);
                if(instruction.at(1) == 0)
                    p1 = opcodes.at(p1);
                if(p1 != 0)
                {
                    if(instruction.at(2) == 0)
                        p2 = opcodes.at(p2);
                    acc = p2;
                } else
                    acc += 3;
                break;
            case 6:
                p1 = opcodes.at(acc+1);
                p2 = opcodes.at(acc+2);
                if(instruction.at(1) == 0)
                    p1 = opcodes.at(p1);
                if(p1 == 0)
                {
                    if(instruction.at(2) == 0)
                        p2 = opcodes.at(p2);
                    acc = p2;
                } else
                    acc += 3;
                break;
            case 7:
                p1 = opcodes.at(acc+1);
                p2 = opcodes.at(acc+2);
                if(instruction.at(1) == 0)
                    p1 = opcodes.at(p1);
                if(instruction.at(2) == 0)
                    p2 = opcodes.at(p2);
                res = 0;
                if(p1 < p2)
                    res = 1;
                if(instruction.at(3) == 0)
                    opcodes.at(opcodes.at(acc+3)) = res;
                else
                    opcodes.at(acc+3) = res;
                acc += 4;
                break;
            case 8:
                p1 = opcodes.at(acc+1);
                p2 = opcodes.at(acc+2);
                if(instruction.at(1) == 0)
                    p1 = opcodes.at(p1);
                if(instruction.at(2) == 0)
                    p2 = opcodes.at(p2);
                res = 0;
                if(p1 == p2)
                    res = 1;
                if(instruction.at(3) == 0)
                    opcodes.at(opcodes.at(acc+3)) = res;
                else
                    opcodes.at(acc+3) = res;
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

    return opcodes[0];
}


int main() {

    ifstream input_file("../input.txt");
    vector<int> opcodes;

    for (int i; input_file >> i;) {
        opcodes.push_back(i);
        if (input_file.peek() == ',')
            input_file.ignore();
    }
    input_file.close();

    program(opcodes);

    return 0;
}
