// Anna Pankiewicz
// CS 5001

#include <iostream>
#include "value_iteration.h"

const float GAMMA = 0.8;              // discount rate
const int START[2] = {1, 1};          // arbitrary starting position

int main()
{
    // Greeting
    std::cout << "CS5001: HW#2" << std::endl
	<< "Programmer: Anna Pankiewicz"<< std::endl
	<< "Discount Gamma = " <<  GAMMA << std::endl;

    // Initialize variables
    int iterations;
    float q_table[10][10][4] = {0};       // Q(s,a) table
    float q_prime[10][10][4] = {0};       // Q prime table
    std::string policy[10][10];           // final policy table

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
