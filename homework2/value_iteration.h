// Anna Pankiewicz
// CS 5001

#include <iostream>

#ifndef VALUE_ITERATION
#define VALUE_ITERATION

enum Action {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

// Tile struct
struct Tile {
    std::string title;
    int reward;
};

void fill_map(Tile** &map);

void prob(float* up, float* right, float* down, float* left, int action);

float value(int x, int y);

float exp_reward(int x, int y, int action, Tile** map);

void value_iterate(int iterations, Tile** map);

void table_copy(float destination[10][10][4], float source[10][10][4]);

void print_table(float table[10][10]);

void print_table(std::string table[10][10]);

#endif
