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
        static std::string generate_drawing(const Puzzle &puzzle);
        static std::string generate_drawing(const Grid &grid);
        static std::string generate_drawing(const std::vector<Figure> figures);
        static std::string generate_drawing(const Figure &figure);
    private:
        static std::string get_formatted_title(std::string title);
};

#endif