#include "puzzle.h"

Puzzle::Puzzle(size_t width, size_t height, std::vector<Figure> figures) : grid(width, height), not_placed_figures(figures) {}

size_t Puzzle::get_width() const
{
    return grid.get_width();
}

size_t Puzzle::get_height() const
{
    return grid.get_height();
}

const Grid& Puzzle::get_const_grid() const
{
    return grid;
}

Grid& Puzzle::get_grid()
{
    return grid;
}

bool Puzzle::is_solved() const
{
    return grid.is_solved();
}

const std::vector<std::pair<Position, Figure>>& Puzzle::get_const_placed_figures() const
{
    return grid.get_const_placed_figures();
}

std::vector<std::pair<Position, Figure>>& Puzzle::get_placed_figures()
{
    return grid.get_placed_figures();
}

const std::vector<Figure>& Puzzle::get_const_not_placed_figures() const
{
    return not_placed_figures;
}

std::vector<Figure>& Puzzle::get_not_placed_figures()
{
    return not_placed_figures;
}

bool Puzzle::can_insert_figure(Position position, int num_figure) const
{
    if (num_figure < 0 || num_figure >= not_placed_figures.size()) return false;
    return grid.can_insert_figure(position, not_placed_figures[num_figure]);
}

bool Puzzle::insert_figure(Position position, int num_figure)
{
    if (num_figure < 0 || num_figure >= not_placed_figures.size()) return false;
    if (!grid.insert_figure(position, not_placed_figures[num_figure])) return false;
    not_placed_figures.erase(not_placed_figures.begin() + num_figure);
    return true;
}

bool Puzzle::remove_figure(int num_figure)
{
    std::vector<std::pair<Position, Figure>> &placed_figures = get_placed_figures();
    if (num_figure < 0 || num_figure >= placed_figures.size()) return false;
    if (!grid.remove_figure(placed_figures[num_figure].second)) return false;
    not_placed_figures.push_back(placed_figures[num_figure].second);
    return true;
}

bool Puzzle::is_position_empty(Position position) const
{
    return grid.is_position_empty(position);
}

char Puzzle::get_letter_from_position(Position position) const
{
    return grid.get_letter_from_position(position);
}

void Puzzle::set_grid(Grid grid)
{
    this->grid = grid;
}

void Puzzle::set_not_placed_figures(std::vector<Figure> not_placed_figures)
{
    this->not_placed_figures = not_placed_figures;
}