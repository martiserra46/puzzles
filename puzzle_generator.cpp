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
    std::vector<std::vector<char>> matrix(rows, std::vector<char>(columns, '\0'));
    while (!is_matrix_fully_generated(matrix, num_figures))
    {
        insert_random_value_in_matrix(matrix, num_figures);
        if (is_impossible_to_generate_matrix(matrix, num_figures))
            fill_matrix(matrix, '\0');
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

void PuzzleGenerator::insert_random_value_in_matrix(std::vector<std::vector<char>> &matrix, int num_figures)
{
    std::vector<Position> positions_empty = get_positions_value_in_matrix(matrix, '\0');

    std::vector<std::vector<Position>> positions_letters;

    for (int i = 0; i < num_figures; i++) positions_letters.push_back(get_positions_value_in_matrix(matrix, 'A' + i));

    while (true)
    {
        int fig_number = random(0, num_figures - 1);
        char letter = 'A' + fig_number;
        std::vector<Position> &positions_letter = positions_letters[fig_number];

        if (positions_letter.size() == 0)
        {
            Position position_to_insert = positions_empty[random(0, positions_empty.size() - 1)];
            matrix[position_to_insert.x][position_to_insert.y] = letter;
            break;
        }
        else
        {
            Position position_to_insert = positions_letter[random(0, positions_letter.size() - 1)];
            int x = random(0, 3);
            if (x == 0) position_to_insert.x += 1;
            else if (x == 1) position_to_insert.y += 1;
            else if (x == 2) position_to_insert.x -= 1;
            else position_to_insert.y -= 1;

            if (matrix[position_to_insert.x][position_to_insert.y] == '\0')
            {
                matrix[position_to_insert.x][position_to_insert.y] = random_letter;
                break;
            }
        }
    }
}

bool PuzzleGenerator::is_impossible_to_generate_matrix(std::vector<std::vector<char>> matrix, int num_figures)
{
    return false;
}