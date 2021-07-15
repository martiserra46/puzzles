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
        static std::string generate_drawing(Puzzle &puzzle);
        static std::string generate_drawing(Grid &grid);
        static std::string generate_drawing(std::vector<Figure> figures);
        static std::string generate_drawing(Figure &figure);
};

#endif