#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using std::ifstream;
using std::cout;
using std::endl;
using std::floor;
using std::string;
using std::stof;

int main() {

    int sum = 0;
    string module;
    ifstream file ("../input.txt");

    if (file.is_open())
    {
        while ( getline (file,module) )
        {
            int mass = int(floor(stof(module)/ 3.0) - 2);
            sum += mass;
        }
        file.close();
    }
    else
    {
        cout << "Couldn't open file" << endl;
    }

    cout << "Sum: " << sum << endl;

    return 0;
}
