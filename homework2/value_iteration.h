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

float value(int x, int y, float ***q_table, std::string *policy);

#endif
