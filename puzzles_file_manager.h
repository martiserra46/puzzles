#ifndef PUZZLES_FILE_MANAGER_H
#define PUZZLES_FILE_MANAGER_H

#include "puzzle.h"

class PuzzlesFileManager
{
    public:
        static void save_puzzle(std::string difficulty, int level_number, Puzzle puzzle);
        static Puzzle load_puzzle(std::string difficulty, int level_number);
};

#endif