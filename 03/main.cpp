#include <iostream>
#include <tuple>
#include <vector>
#include <fstream>
#include <string>
using std::tuple;
using std::get;
using std::vector;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::stoi;

//change maximum to reduce intersection time
const int MAXIMUM_DISTANCE = 3000;
const int MAXIMUM_STEPS = 500;

int manhattan_distance(tuple<int, int> a, tuple<int, int> b)
{
    return abs(get<0>(a) - get<0>(b)) + abs(get<1>(a) - get<1>(b));
}

vector<tuple<int, int>> calc_wire(tuple<int, int> pos, vector<string> moves)
{
    vector<tuple<int, int>> rc;
    int steps = 0;
    for(auto & move : moves)
    {
        steps++;
        if(steps > MAXIMUM_STEPS)
            break;
        char direction = move[0];
        string len;
        for(int i = 1; i < move.size(); ++i)
        {
            len.push_back(move[i]);
        }
        int steps = stoi(len);
        switch(direction)
        {
            case 'R':
                for(int i = 0; i < steps; ++i)
                {
                    get<0>(pos) += 1;
                    if(abs(get<0>(pos)) < MAXIMUM_DISTANCE && abs(get<1>(pos)) < MAXIMUM_DISTANCE)
                        rc.emplace_back(pos);
                }
                break;
            case 'L':
                for(int i = 0; i < steps; ++i)
                {
                    get<0>(pos) -= 1;
                    if(abs(get<0>(pos)) < MAXIMUM_DISTANCE && abs(get<1>(pos)) < MAXIMUM_DISTANCE)
                        rc.emplace_back(pos);
                }
                break;
            case 'U':
                for(int i = 0; i < steps; ++i)
                {
                    get<1>(pos) += 1;
                    if(abs(get<0>(pos)) < MAXIMUM_DISTANCE && abs(get<1>(pos)) < MAXIMUM_DISTANCE)
                        rc.emplace_back(pos);
                }
                break;
            case 'D':
                for(int i = 0; i < steps; ++i)
                {
                    get<1>(pos) -= 1;
                    if(abs(get<0>(pos)) < MAXIMUM_DISTANCE && abs(get<1>(pos)) < MAXIMUM_DISTANCE)
                        rc.emplace_back(pos);
                }
                break;
            default:
                break;
        }

    }
    return rc;
}

vector<tuple<int, int>> find_intersections(const vector<tuple<int, int>> wire1, vector<tuple<int, int>> wire2)
{
    vector<tuple<int, int>> intersections;
    int i = 0;
    for(auto & pos1 : wire1)
    {
        for(auto & pos2 : wire2)
        {
            if(get<0>(pos1) == get<0>(pos2) && get<1>(pos1) == get<1>(pos2))
            {
                intersections.emplace_back(pos1);
            }
        }
    }
    return intersections;
}

int steps_to_reach(tuple<int, int> goal, vector<string> moves)
{
    tuple<int, int> pos(0,0);
    bool found = false;
    int step = 0;
    for(auto & move : moves)
    {
        if(found)
            break;
        char direction = move[0];
        string len;
        for(int i = 1; i < move.size(); ++i)
        {
            len.push_back(move[i]);
        }
        int steps = stoi(len);
        switch(direction)
        {
            case 'R':
                for(int i = 0; i < steps && !found; ++i)
                {
                    get<0>(pos) += 1;
                    step++;
                    if(get<0>(pos) == get<0>(goal) && get<1>(pos) == get<1>(goal))
                        found = true;
                }
                break;
            case 'L':
                for(int i = 0; i < steps && !found; ++i)
                {
                    get<0>(pos) -= 1;
                    step++;
                    if(get<0>(pos) == get<0>(goal) && get<1>(pos) == get<1>(goal))
                        found = true;
                }
                break;
            case 'U':
                for(int i = 0; i < steps && !found; ++i)
                {
                    get<1>(pos) += 1;
                    step++;
                    if(get<0>(pos) == get<0>(goal) && get<1>(pos) == get<1>(goal))
                        found = true;
                }
                break;
            case 'D':
                for(int i = 0; i < steps && !found; ++i)
                {
                    get<1>(pos) -= 1;
                    step++;
                    if(get<0>(pos) == get<0>(goal) && get<1>(pos) == get<1>(goal))
                        found = true;
                }
                break;
            default:
                break;
        }

    }

    return step;
}

int main()
{
    //input all
    ifstream in("../input.txt");
    vector<string> wire1;
    vector<string> wire2;

    string move;
    while(getline(in, move, ','))
    {
        wire1.push_back(move);
        if(in.peek() == '\n')
        {
            in.ignore();
            break;
        }
    }

    while(getline(in, move, ','))
    {
        wire2.push_back(move);
        if(in.peek() == '\n')
        {
            in.ignore();
            break;
        }
    }

    //find all intersections
    tuple<int, int> origin(0,0);
    vector<tuple<int,int>> intersections = find_intersections(calc_wire(origin, wire1), calc_wire(origin, wire2));


    //calculate closest intersection (to origin (0,0))
    tuple<int, int> closest(intersections[0]);
    int distance = manhattan_distance(origin, intersections[0]);


    for(int i = 0; i < intersections.size(); ++i)
    {
        int man_dis = manhattan_distance(origin, intersections[i]);
        if(man_dis < distance)
        {
            distance = man_dis;
            closest = intersections[i];
        }
    }

    //result task 1
    cout << endl;
    cout << "(" << get<0>(closest) << ", " << get<1>(closest) << ")" << endl;
    cout << "distance = " << distance << endl;


    //calculate closest intersection (to origin (0,0))
    tuple<int, int> closest_steps(intersections[0]);
    int distance_steps = steps_to_reach(intersections[0], wire1) + steps_to_reach(intersections[0], wire2);


    for(int i = 0; i < intersections.size(); ++i)
    {
        int step_dis = steps_to_reach(intersections[i], wire1) + steps_to_reach(intersections[i], wire2);
        if(step_dis < distance_steps)
        {
            distance_steps = step_dis;
            closest_steps = intersections[i];
        }
    }

    // result task 2
    int steps1 = steps_to_reach(closest_steps, wire1);
    int steps2 = steps_to_reach(closest_steps, wire2);
    cout << endl;
    cout << "(" << get<0>(closest_steps) << ", " << get<1>(closest_steps) << ")" << endl;
    cout << "steps1 = " <<  steps1 << endl;
    cout << "steps2 = " <<  steps2 << endl;
    cout << "distance steps = " <<  distance_steps << endl;

    return 0;
}
