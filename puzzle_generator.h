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
        static bool is_matrix_fully_generated(std::vector<std::vector<char>> matrix, int num_figures);
        static void insert_random_value_in_matrix(std::vector<std::vector<char>> &matrix, int num_figures);
        static bool is_impossible_to_generate_matrix(std::vector<std::vector<char>> matrix, int num_figures);
};

#endif