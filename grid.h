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
        Grid(size_t width = 0, size_t height = 0);
        size_t get_width() const;
        size_t get_height() const;
        bool is_solved() const;
        const std::vector<std::pair<Position, Figure>>& get_const_placed_figures() const;
        std::vector<std::pair<Position, Figure>>& get_placed_figures();
        bool can_insert_figure(Position position, const Figure &figure) const;
        bool insert_figure(Position position, const Figure &figure);
        bool remove_figure(const Figure &figure);
        bool is_position_empty(Position position) const;
        char get_letter_from_position(Position position) const;
        friend std::istream& operator>>(std::istream& is, Grid& grid);
    private:
        void set_width(size_t width);
        void set_height(size_t height);
        void set_placed_figures(const std::vector<std::pair<Position, Figure>> placed_figures);
};

#endif