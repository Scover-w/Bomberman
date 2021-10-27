#pragma once
#include <iostream>
using namespace std;

typedef tuple<int, int, int> Tuple;

typedef struct Cell Cell;

struct Cell
{
    Vector2i parent;

    int f, g, h;
    Cell() : parent(-1, -1), f(-1), g(-1), h(-1)
    {}
};

