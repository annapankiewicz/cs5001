// Anna Pankiewicz
// CS 5001

#include <iostream>

#ifndef VALUE_ITERATION
#define VALUE_ITERATION

struct Tile {
    bool valid;
    std::string title;
    int reward;
};

void fill_map(Tile** &map);

#endif
