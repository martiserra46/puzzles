#include "grid.h"

Grid::Grid(size_t width, size_t height)
{
    this->width = width;
    this->height = height;
}

size_t Grid::get_width() const
{
    return width;
}

size_t Grid::get_height() const
{
    return height;
}

bool Grid::is_solved() const
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (is_position_empty({j, i})) return false;
        }
    }
    return true;
}

const std::vector<std::pair<Position, Figure>>& Grid::get_const_placed_figures() const
{
    return placed_figures;
}

std::vector<std::pair<Position, Figure>>& Grid::get_placed_figures()
{
    return placed_figures;
}

bool Grid::can_insert_figure(Position position, const Figure &figure) const
{
    std::set<Position> figure_positions = figure.get_positions();
    for (Position figure_position : figure_positions)
    {
        Position position_in_grid = position + figure_position;
        if (position_in_grid.x < 0 || position_in_grid.x >= width) return false;
        if (position_in_grid.y < 0 || position_in_grid.y >= height) return false;
        if (!is_position_empty(position_in_grid)) return false;
    }
    return true;
}

bool Grid::insert_figure(Position position, const Figure &figure)
{
    if (!can_insert_figure(position, figure)) return false;
    placed_figures.push_back({position, figure});
    return true;
}

bool Grid::remove_figure(int num_figure)
{
    if (num_figure < 0 || num_figure >= placed_figures.size()) return false;
    placed_figures.erase(placed_figures.begin() + num_figure);
    return true;
}

bool Grid::is_position_empty(Position position) const
{
    return get_letter_from_position(position) == '\0';
}

char Grid::get_letter_from_position(Position position) const
{
    for (std::pair<Position, Figure> placed_figure : placed_figures)
    {
        Position &figure_position_in_grid = placed_figure.first;
        Figure &figure = placed_figure.second;
        for (Position figure_position : figure.get_positions())
        {
            Position position_in_grid = figure_position_in_grid + figure_position;
            if (position == position_in_grid)
            {
                return figure.get_letter();
            }
        }
    }
    return '\0';
}

void Grid::set_width(size_t width)
{
    this->width = width;
}

void Grid::set_height(size_t height)
{
    this->height = height;
}

void Grid::set_placed_figures(const std::vector<std::pair<Position, Figure>> placed_figures)
{
    this->placed_figures = placed_figures;
}