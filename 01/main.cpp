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
using std::max;

int main() {

    int sum = 0;
    string module;
    ifstream file ("../input.txt");

    if (file.is_open())
    {
        while ( getline (file,module) )
        {
            int mass = int(floor(stof(module)/ 3.0) - 2);

            int extra = mass;
            int fuel = 0;
            while(extra > 0)
            {
                extra = max(0, int(floor(float(extra)/ 3.0) - 2));
                fuel += extra;
            }

            sum += mass + fuel;
        }
        file.close();
    }
    else
    {
        cout << "Couldn't open file" << endl;
    }

    cout << "Sum fuel: " << sum << endl;


    return 0;
}
