#ifndef GRID_H
#define GRID_H

#include "figure.h"
#include "position.h"
#include <vector>
#include <utility>
#include <string>

class Grid
{
    size_t width, height;
    std::vector<std::pair<Position, Figure>> placed_figures;
    public:
        Grid(size_t width, size_t height);
        size_t get_width();
        size_t get_height();
        bool is_solved();
        std::vector<std::pair<Position, Figure>>& get_placed_figures();
        bool can_insert_figure(Position position, Figure &figure);
        bool insert_figure(Position position, Figure &figure);
        bool remove_figure(Figure &figure);
        bool is_position_empty(Position position);
        char get_letter_from_position(Position position);
};

#endif