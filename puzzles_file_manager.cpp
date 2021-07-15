#include "puzzles_file_manager.h"
#include <fstream>
#include "position.h"
#include "figure.h"
#include <set>
#include <vector>
#include <iostream>

void PuzzlesFileManager::save_puzzle(std::string difficulty, int level_number, Puzzle puzzle)
{

}

Puzzle PuzzlesFileManager::load_puzzle(std::string difficulty, int level_number)
{
    return Puzzle(5,5,{});
}

std::ostream& operator<<(std::ostream& os, const Puzzle& puzzle)
{
    os << puzzle.get_const_grid() << ' ' << puzzle.get_const_not_placed_figures().size() << ' ';
    for (Figure figure : puzzle.get_const_not_placed_figures())
        os << figure << ' ';
    return os;
}

std::istream& operator>>(std::istream& is, Puzzle& puzzle)
{
    Grid grid(0,0);
    std::vector<Figure> not_placed_figures;
    int num_not_placed_figures;
    
    is >> grid >> num_not_placed_figures;

    Figure figure('\0', {});

    for (int i = 0; i < num_not_placed_figures; i++)
    {
        is >> figure;
        not_placed_figures.push_back(figure);
    }

    puzzle.set_grid(grid);
    puzzle.set_not_placed_figures(not_placed_figures);

    return is;
}

std::ostream& operator<<(std::ostream& os, const Grid& grid)
{
    os << grid.get_width() << ' ' << grid.get_height() << ' ' << grid.get_const_placed_figures().size() << ' ';
    for (std::pair<Position, Figure> placed_figure : grid.get_const_placed_figures())
        os << placed_figure.first << ' ' << placed_figure.second << ' ';
    return os;
}

std::istream& operator>>(std::istream& is, Grid& grid)
{
    size_t width, height;
    int num_placed_figures;

    is >> width >> height >> num_placed_figures;

    std::vector<std::pair<Position, Figure>> placed_figures;

    std::pair<Position, Figure> placed_figure = { Position(), Figure('\0', {}) };

    for (int i = 0; i < num_placed_figures; i++)
    {
        is >> placed_figure.first >> placed_figure.second;
        placed_figures.push_back(placed_figure);
    }

    grid.set_width(width);
    grid.set_height(height);
    grid.set_placed_figures(placed_figures);

    return is;
}

std::ostream& operator<<(std::ostream& os, const Figure& figure)
{
    os << figure.get_letter() << ' ' << figure.get_positions().size() << ' ';
    for (Position position : figure.get_positions())
        os << position << ' ';
    return os;
}

std::istream& operator>>(std::istream& is, Figure& figure)
{
    char letter;
    std::set<Position> positions;

    int num_positions;
    Position position;

    is >> letter >> num_positions;

    for (int i = 0; i < num_positions; i++)
    {
        is >> position;
        positions.insert(position);
    }
    figure.set_letter(letter);
    figure.set_positions(positions);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Position& position)
{
    os << position.x << ',' << position.y;
    return os;
}

std::istream& operator>>(std::istream& is, Position& position)
{
    char comma;
    int x, y;
    is >> x >> comma >> y;
    if (comma != ',') is.setstate(std::ios::failbit);
    position.x = x;
    position.y = y;
    return is;
}