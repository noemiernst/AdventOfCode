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


int program(vector<int> opcodes, int noun, int verb)
{
    opcodes.at(1) = noun;
    opcodes.at(2) = verb;

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

    for (size_t i = 0; i < opcodes.size(); i++)
        cout << opcodes[i] << endl;

    int output = 0;
    int noun = 0;
    int verb = 0;
    for(;output != 19690720 && noun < 100; ++noun)
    {
        verb = 0;
        for(;output != 19690720 && verb < 100; ++verb)
        {
            vector<int> inp;
            for (size_t i = 0; i < opcodes.size(); i++)
                inp.push_back(opcodes[i]);
            output = program(inp, noun, verb);
        }
    }
    --verb;
    --noun;


    cout << "Output: " << output << endl;
    cout << "Noun: " << noun << endl;
    cout << "Verb: " << verb << endl;
    cout << "100 * noun + verb = " << 100*noun+verb << endl;

    return 0;
}
