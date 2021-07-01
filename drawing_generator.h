#ifndef DRAWING_GENERATOR_H
#define DRAWING_GENERATOR_H

#include "grid.h"
#include "figure.h"
#include <vector>
#include <string>

class DrawingGenerator
{
    public:
        std::string generate_drawing(Grid &grid);
        std::string generate_drawing(Figure &figure);
        std::string generate_drawing(std::vector<Figure> figures);
};

#endif