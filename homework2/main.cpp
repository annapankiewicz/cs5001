// Anna Pankiewicz
// CS 5001

#include <iostream>
#include "value_iteration.h"

float GAMMA = 0.8;

int main()
{
    // Greeting
    std::cout << "CS5001: HW#2" << std::endl
	<< "Programmer: Anna Pankiewicz"<< std::endl
	<< "Discount Gamma = " <<  GAMMA << std::endl;

    // Get # of iterations
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
