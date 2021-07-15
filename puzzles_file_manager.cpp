#include "puzzles_file_manager.h"

void PuzzlesFileManager::save_puzzle(std::string difficulty, int level_number, Puzzle puzzle)
{

}

Puzzle PuzzlesFileManager::load_puzzle(std::string difficulty, int level_number)
{
    return Puzzle(5,5,{});
}

std::ostream& operator<<(std::ostream& os, const Puzzle& puzzle)
{
    return os;
}

std::istream& operator>>(std::istream& is, Puzzle& puzzle)
{
    return is;
}

std::ostream& operator<<(std::ostream& os, const Grid& grid)
{
    return os;
}

std::istream& operator>>(std::istream& is, Grid& grid)
{
    return is;
}

std::ostream& operator<<(std::ostream& os, const Figure& figure)
{
    return os;
}

std::istream& operator>>(std::istream& is, Figure& figure)
{
    return is;
}

std::ostream& operator<<(std::ostream& os, const Position& position)
{
    return os;
}

std::istream& operator>>(std::istream& is, Position& position)
{
    return is;
}