// Anna Pankiewicz
// CS 5001

#include <iostream>
#include "value_iteration.h"

const float GAMMA = 0.8;              // discount rate
float q_table[10][10][4] = {0};       // Q(s,a) table
float q_prime[10][10][4] = {0};       // Q prime table
std::string policy[10][10];           // final policy table

int main()
{
    // Greeting
    std::cout << "CS5001: HW#2" << std::endl
	<< "Programmer: Anna Pankiewicz"<< std::endl
	<< "Discount Gamma = " <<  GAMMA << std::endl;

    // Initialize variables
    int iterations;

    std::cout << "Enter number of iterations:" << std::endl;
    std::cin >> iterations;

    // Create map
    Tile** map = new Tile*[10];
    for(int i=0; i<10; i++)
    {
        map[i] = new Tile[10];
    }

    fill_map(map);

    for(int i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
            std::cout<<map[i][j].title<<" ";
        std::cout<<std::endl;
    }
    
    // Cleanup
    for(int i=0; i<10; i++)
    {
        delete [] map[i];
    }
    delete [] map;
    return 0;
}


/*
The function fill_map takes in a 2D Tile array and assigns obstacles
as given in the problem description, and additonally assigns the
appropriate reward to each space.
*/
void fill_map(Tile** &map)
{
    // initialize everything to a blank space
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
        {
            map[i][j]={"-----",0};
        }
    }

    // fill in outer walls
    for(int i=0; i<10; i++)
    {
        map[0][i] = {"wall ",-1};
        map[9][i] = {"wall ",-1};
        map[i][0] = {"wall ",-1};
        map[i][9] = {"wall ",-1};
    }

    // fill in inner random walls
    map[3][2] = {"wall ",-1};
    map[3][3] = {"wall ",-1};
    map[6][3] = {"wall ",-1};
    map[6][4] = {"wall ",-1};
    map[6][5] = {"wall ",-1};
    map[5][5] = {"wall ",-1};
    map[4][5] = {"wall ",-1};
    map[4][6] = {"wall ",-1};

    // fill in other miscellaneous spaces
    map[2][5] = {"donut",3};
    map[4][2] = {"fire ",-5};
    map[6][7] = {"cake ",10};
    map[7][3] = {"oni  ",-10};

    return;
}

/*
The function prob takes in four pointers to represent the probabilities of
each direction that can be taken, and an action. For the appropriate action,
probability values are accordingly assigned.
*/
void prob(float* up, float* right, float* down, float* left, int action)
{
    switch(action) {
        case(UP):
            *up = 0.85;
            *right = 0.09;
            *down = 0.0;
            *left = 0.09;
            break;
        case(RIGHT):
            *up = 0.09;
            *right = 0.85;
            *down = 0.09;
            *left = 0.0;
            break;
        case(DOWN):
            *up = 0.0;
            *right = 0.09;
            *down = 0.85;
            *left = 0.09;
            break;
        case(LEFT):
            *up = 0.09;
            *right = 0.0;
            *down = 0.09;
            *left = 0.85;
            break;
        default:
            std::cout << "Error: not valid direction" << std::endl;
            break;
        return;
    }
}

float value(int x, int y)
{
    float max_value = 0.0;
    if(q_table[y][x][UP] > max_value)
    {
        max_value = q_table[y][x][UP];
        policy[y][x] = '^';
    }
    if(q_table[y][x][RIGHT] > max_value)
    {
        max_value = q_table[y][x][RIGHT];
        policy[y][x] = '>';
    }
    if(q_table[y][x][DOWN] > max_value)
    {
        max_value = q_table[y][x][DOWN];
        policy[y][x] = 'v';
    }
    if(q_table[y][x][LEFT] > max_value)
    {
        max_value = q_table[y][x][LEFT];
        policy[y][x] = '<';
    }
    return max_value;
}

float exp_reward(int x, int y, int action, Tile** map)
{
    float reward = 0.0;
    float *up, *right, *down, *left;

    prob(up, right, down, left, action);
    reward += (*up * map[y][x+1].reward);
    reward += (*right * map[y+1][x].reward);
    reward += (*down * map[y][x-1].reward);
    reward += (*left * map[y-1][x].reward);

    return reward;
}

void value_iterate(int iterations, Tile** map)
{
    float temp_value;
    float *up, *right, *down, *left;
    for(int i = 0; i < iterations; i++)
    {
        // for every location y,x
        for(int y_coord = 1; y_coord < 9; y_coord++)
        {
            for(int x_coord = 1; x_coord < 9; x_coord++)
            {
                // for every action possible from that location
                for(int action = 0; action < 4; action++)
                {
                    temp_value = 0.0;
                    prob(up, right, down, left, action);
                    temp_value += *up * value(x_coord, y_coord+1);
                    temp_value += *right * value(x_coord+1, y_coord);
                    temp_value += *down * value(x_coord, y_coord-1);
                    temp_value += *left * value(x_coord-1, y_coord);
                    q_prime[y_coord][x_coord][action] = exp_reward(x_coord, y_coord, action, map);
                }
            }
        }
    }
    table_copy(q_table, q_prime);
}

void table_copy(float destination[10][10][4], float source[10][10][4])
{
    for(int x = 0; x < 9; x++)
    {
        for(int y = 0; y < 9; y++)
        {
            for(int a = 0; a < 4; a++)
            {
                destination[x][y][a] = source[x][y][a];
            }
        }
    }
}