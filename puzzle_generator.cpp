#include "puzzle_generator.h"
#include <vector>
#include "number_utils.h"

Puzzle PuzzleGenerator::generate_puzzle(int rows, int columns, int num_figures)
{
    std::vector<std::vector<char>> matrix = generate_matrix(rows, columns, num_figures);
    std::vector<Figure> figures = get_figures_from_matrix(matrix);
    return Puzzle(rows, columns, figures);
}

std::vector<std::vector<char>> PuzzleGenerator::generate_matrix(int rows, int columns, int num_figures)
{
    return {};
}

std::vector<Figure> PuzzleGenerator::get_figures_from_matrix(std::vector<std::vector<char>> matrix)
{
    return {};
}
