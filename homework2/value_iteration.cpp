// Anna Pankiewicz
// CS 5001

#include "value_iteration.h"

void fill_map(Tile** &map)
{   
    // initialize everything to a blank space
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
        {
            map[i][j]={true,"-----"};
        }
    }

    // fill in outer walls
    for(int i=0; i<10; i++)
    {
        map[0][i] = {false,"wall ",-1};
        map[9][i] = {false,"wall ",-1};
        map[i][0] = {false,"wall ",-1};
        map[i][9] = {false,"wall ",-1};
    }

    // fill in inner random walls
    map[3][2] = {false,"wall ",-1};
    map[3][3] = {false,"wall ",-1};
    map[6][3] = {false,"wall ",-1};
    map[6][4] = {false,"wall ",-1};
    map[6][5] = {false,"wall ",-1};
    map[5][5] = {false,"wall ",-1};
    map[4][5] = {false,"wall ",-1};
    map[4][6] = {false,"wall ",-1};

    // fill in other miscellaneous spaces
    map[2][5] = {true,"donut",3};
    map[4][2] = {true,"fire ",-5};
    map[6][7] = {true,"cake ",10};
    map[7][3] = {true,"oni  ",-10};

    return;
}