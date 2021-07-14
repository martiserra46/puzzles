#include "puzzle_generator.h"
#include <vector>
#include "number_utils.h"
#include "vector_utils.h"

Puzzle PuzzleGenerator::generate_puzzle(int rows, int columns, int num_figures)
{
    std::vector<std::vector<char>> matrix = generate_matrix(rows, columns, num_figures);
    std::vector<Figure> figures = get_figures_from_matrix(matrix);
    return Puzzle(rows, columns, figures);
}

std::vector<std::vector<char>> PuzzleGenerator::generate_matrix(int rows, int columns, int num_figures)
{
    std::vector<std::vector<char>> matrix(rows, std::vector<char>(columns, '\0'));
    while (!is_matrix_fully_generated(matrix, num_figures))
    {
        insert_random_value_in_matrix(matrix, num_figures);
        if (is_impossible_to_generate_matrix(matrix, num_figures))
            matrix = std::vector<std::vector<char>>(rows, std::vector<char>(columns, '\0'));
    }
    return matrix;
}

std::vector<Figure> PuzzleGenerator::get_figures_from_matrix(std::vector<std::vector<char>> matrix)
{
    return {};
}

bool PuzzleGenerator::is_matrix_fully_generated(std::vector<std::vector<char>> matrix, int num_figures)
{
    if (is_value_in_matrix(matrix, '\0')) return false;
    for (int i = 0; i < num_figures; i++)
        if (!is_value_in_matrix(matrix, 'A' + i)) return false;
    return true;
}

void PuzzleGenerator::insert_random_value_in_matrix(std::vector<std::vector<char>> matrix, int num_figures)
{
    
}    

bool PuzzleGenerator::is_impossible_to_generate_matrix(std::vector<std::vector<char>> matrix, int num_figures)
{
    return false;
}