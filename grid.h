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
        size_t get_width() const;
        size_t get_height() const;
        bool is_solved() const;
        const std::vector<std::pair<Position, Figure>>& get_placed_figures() const;
        bool can_insert_figure(Position position, Figure &figure) const;
        bool insert_figure(Position position, Figure &figure);
        bool remove_figure(Figure &figure);
        bool is_position_empty(Position position) const;
        char get_letter_from_position(Position position) const;
};

#endif