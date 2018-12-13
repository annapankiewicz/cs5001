// Anna Pankiewicz
// CS 5001

#include "value_iteration.h"

/*
The function fill_map takes in a 2D Tile array and assigns obstacles
as given in the problem description, and additonally assigns the
1appropriate reward to each space.
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

float value(int x, int y, float ***q_table, std::string *policy)
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