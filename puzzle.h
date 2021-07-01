#ifndef PUZZLE_H
#define PUZZLE_H

#include "position.h"
#include <vector>
#include <utility>
#include <string>
#include "figure.h"
#include "grid.h"

class Puzzle
{
    Grid grid;
    std::vector<Figure> not_placed_figures;
    
    public:
        Puzzle(size_t width, size_t height, std::vector<Figure> figures);
        size_t get_width();
        size_t get_height();
        bool is_solved();
        std::vector<std::pair<Position, Figure>>& get_placed_figures();
        std::vector<Figure>& get_not_placed_figures();
        bool can_insert_figure(Position position, int num_figure);
        bool insert_figure(Position position, int num_figure);
        bool remove_figure(int num_figure);
        bool is_position_empty(Position position);
        char get_letter_from_position(Position position);
};

#endif