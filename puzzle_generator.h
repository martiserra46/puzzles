#ifndef LEVEL_GENERATOR_H
#define LEVEL_GENERATOR_H

#include "puzzle.h"

class PuzzleGenerator
{
    public:
        static Puzzle generate_puzzle(int rows, int columns, int num_figures);
    private:
        static std::vector<std::vector<char>> generate_matrix(int rows, int columns, int num_figures);
        static std::vector<Figure> get_figures_from_matrix(std::vector<std::vector<char>> matrix);
};

#endif