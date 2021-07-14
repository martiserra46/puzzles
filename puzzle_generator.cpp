#include "puzzle_generator.h"
#include <vector>
#include "number_utils.h"
#include "vector_utils.h"
#include "position.h"

Puzzle PuzzleGenerator::generate_puzzle(int rows, int columns, int num_figures)
{
    std::vector<std::vector<char>> matrix = generate_matrix(rows, columns, num_figures);
    std::vector<Figure> figures = get_figures_from_matrix(matrix);
    return Puzzle(rows, columns, figures);
}

std::vector<std::vector<char>> PuzzleGenerator::generate_matrix(int rows, int columns, int num_figures)
{
    auto matrix = create_matrix(rows, columns);
    while (!is_matrix_fully_generated(matrix, num_figures))
    {
        if (can_insert_random_value_in_matrix(matrix, num_figures))
            insert_random_value_in_matrix(matrix, num_figures);
        else
            fill_matrix(matrix, '\0');
    }
    return matrix;
}

std::vector<Figure> PuzzleGenerator::get_figures_from_matrix(std::vector<std::vector<char>> &matrix)
{
    return {};
}

bool PuzzleGenerator::is_matrix_fully_generated(std::vector<std::vector<char>> &matrix, int num_figures)
{
    if (is_value_in_matrix(matrix, '\0')) return false;
    for (int i = 0; i < num_figures; i++)
        if (!is_value_in_matrix(matrix, 'A' + i)) return false;
    return true;
}

void PuzzleGenerator::insert_random_value_in_matrix(std::vector<std::vector<char>> &matrix, int num_figures)
{
    bool has_inserted = false;

    std::vector<Position> positions_empty = get_positions_value_in_matrix(matrix, '\0');

    while (!has_inserted)
    {
        int fig_number = random(0, num_figures - 1);
        char letter = 'A' + fig_number;

        Position position_to_insert = positions_empty[random(0, positions_empty.size() - 1)];

        if (can_insert_value_in_matrix(matrix, num_figures, letter, position_to_insert))
        {
            matrix[position_to_insert.x][position_to_insert.y] = letter;
            has_inserted = true;
        }
    }
}

bool PuzzleGenerator::can_insert_random_value_in_matrix(std::vector<std::vector<char>> &matrix, int num_figures)
{
    for (int fig_number = 0; fig_number < num_figures; fig_number++)
    {
        char letter = 'A' + fig_number;
        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[i].size(); j++)
            {
                if (can_insert_value_in_matrix(matrix, num_figures, letter, {i, j})) return true;
            }
        }
    }
    return false;
}

bool PuzzleGenerator::can_insert_value_in_matrix(std::vector<std::vector<char>> &matrix, int num_figures, int letter, Position position)
{
    if (matrix[position.x][position.y] != '\0') return false;

    auto positions_letter = get_positions_value_in_matrix(matrix, letter);

    if (positions_letter.size() == 0) return true;

    if (position.x < matrix.size() - 1 && matrix[position.x + 1][position.y] == letter) return true;
    if (position.y < matrix[position.x].size() - 1 && matrix[position.x][position.y + 1] == letter) return true;
    if (position.x > 0 && matrix[position.x - 1][position.y] == letter) return true;
    if (position.y > 0 && matrix[position.x][position.y - 1] == letter) return true;

    return false;
}