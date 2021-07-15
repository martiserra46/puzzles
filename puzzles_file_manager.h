#ifndef PUZZLES_FILE_MANAGER_H
#define PUZZLES_FILE_MANAGER_H

#include "puzzle.h"

class PuzzlesFileManager
{
    public:
        static void save_puzzle(std::string difficulty, int level_number, Puzzle puzzle);
        static Puzzle load_puzzle(std::string difficulty, int level_number);
    private:
        std::string get_file_path(std::string difficulty, int level_number);
};

std::ostream& operator<<(std::ostream& os, const Puzzle& puzzle);
std::istream& operator>>(std::istream& is, Puzzle& puzzle);

std::ostream& operator<<(std::ostream& os, const Grid& grid);
std::istream& operator>>(std::istream& is, Grid& grid);

std::ostream& operator<<(std::ostream& os, const Figure& figure);
std::istream& operator>>(std::istream& is, Figure& figure);

std::ostream& operator<<(std::ostream& os, const Position& position);
std::istream& operator>>(std::istream& is, Position& position);

#endif