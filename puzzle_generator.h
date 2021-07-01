#ifndef LEVEL_GENERATOR_H
#define LEVEL_GENERATOR_H

#include "puzzle.h"

class PuzzleGenerator
{
    public:
        static Puzzle generate_puzzle(int rows, int columns, int num_figures);
};

#endif