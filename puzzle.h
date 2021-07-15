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
        Puzzle(size_t width = 0, size_t height = 0, std::vector<Figure> figures = {});
        size_t get_width() const;
        size_t get_height() const;
        const Grid& get_const_grid() const;
        Grid& get_grid();
        bool is_solved() const;
        const std::vector<std::pair<Position, Figure>>& get_const_placed_figures() const;
        std::vector<std::pair<Position, Figure>>& get_placed_figures();
        const std::vector<Figure>& get_const_not_placed_figures() const;
        std::vector<Figure>& get_not_placed_figures();
        bool can_insert_figure(Position position, int num_figure) const;
        bool insert_figure(Position position, int num_figure);
        bool remove_figure(int num_figure);
        bool is_position_empty(Position position) const;
        char get_letter_from_position(Position position) const;
        friend std::istream& operator>>(std::istream& is, Puzzle& puzzle);
    private:
        void set_grid(Grid grid);
        void set_not_placed_figures(std::vector<Figure> not_placed_figures);
};

#endif