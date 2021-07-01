#ifndef DRAWING_GENERATOR_H
#define DRAWING_GENERATOR_H

#include "puzzle.h"
#include "grid.h"
#include "figure.h"
#include <vector>
#include <string>

class DrawingGenerator
{
    public:
        std::string generate_drawing(Puzzle &puzzle);
        std::string generate_drawing(Grid &grid);
        std::string generate_drawing(std::vector<Figure> figures);
        std::string generate_drawing(Figure &figure);
};

#endif