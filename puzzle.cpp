#include "puzzle.h"

Puzzle::Puzzle(size_t width, size_t height, std::vector<Figure> figures) : grid(width, height), not_placed_figures(figures) {}

size_t Puzzle::get_width()
{
    return grid.get_width();
}

size_t Puzzle::get_height()
{
    return grid.get_height();
}

Grid& Puzzle::get_grid()
{
    return grid;
}

bool Puzzle::is_solved()
{
    return grid.is_solved();
}

std::vector<std::pair<Position, Figure>>& Puzzle::get_placed_figures()
{
    return grid.get_placed_figures();
}

std::vector<Figure>& Puzzle::get_not_placed_figures()
{
    return not_placed_figures;
}

bool Puzzle::can_insert_figure(Position position, int num_figure)
{
    if (num_figure < 0 || num_figure >= not_placed_figures.size()) return false;
    return grid.can_insert_figure(position, not_placed_figures[num_figure]);
}

bool Puzzle::insert_figure(Position position, int num_figure)
{
    if (num_figure < 0 || num_figure >= not_placed_figures.size()) return false;
    return grid.insert_figure(position, not_placed_figures[num_figure]);
}

bool Puzzle::remove_figure(int num_figure)
{
    std::vector<std::pair<Position, Figure>> &placed_figures = get_placed_figures();
    if (num_figure < 0 || num_figure >= placed_figures.size()) return false;
    return grid.remove_figure(placed_figures[num_figure].second);
}

bool Puzzle::is_position_empty(Position position)
{
    return grid.is_position_empty(position);
}

char Puzzle::get_letter_from_position(Position position)
{
    return grid.get_letter_from_position(position);
}