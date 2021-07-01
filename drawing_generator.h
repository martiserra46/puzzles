#ifndef DRAWING_GENERATOR_H
#define DRAWING_GENERATOR_H

#include "grid.h"
#include "figure.h"

class DrawingGenerator
{
    public:
        std::string generate_drawing(Grid &grid);
        std::string generate_drawing(Figure &figure);
};

#endif