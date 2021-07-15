#include "puzzle_generator.h"
#include <vector>
#include <set>
#include "number_utils.h"
#include "vector_utils.h"
#include "position.h"
#include "figure.h"

Puzzle PuzzleGenerator::generate_puzzle(int rows, int columns, int num_figures)
{
    std::vector<std::vector<char>> matrix = generate_matrix(rows, columns, num_figures);
    std::vector<Figure> figures = get_figures_from_matrix(matrix, num_figures);
    return Puzzle(rows, columns, figures);
}

std::vector<std::vector<char>> PuzzleGenerator::generate_matrix(int rows, int columns, int num_figures)
{
    auto matrix = create_matrix(rows, columns);

    while (is_value_in_matrix(matrix, '\0'))
    {
        insert_random_value_in_matrix(matrix, num_figures);
        if (!is_value_in_matrix(matrix, '\0') && !is_matrix_valid(matrix, num_figures))
            fill_matrix(matrix, '\0');
    }

    return matrix;
}

std::vector<Figure> PuzzleGenerator::get_figures_from_matrix(std::vector<std::vector<char>> &matrix, int num_figures)
{
    std::vector<Figure> figures;
    for (int fig_number = 0; fig_number < num_figures; fig_number++)
    {
        char letter = 'A' + fig_number;
        figures.push_back(get_figure_from_matrix(matrix, letter));
    }
    return figures;
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

bool PuzzleGenerator::is_matrix_valid(std::vector<std::vector<char>> &matrix, int num_figures)
{
    if (is_value_in_matrix(matrix, '\0')) return false;
    int num_positions = matrix.size() * matrix[0].size();
    int mean_num_figure_positions = num_positions / num_figures;
    if (num_positions % num_figures != 0) mean_num_figure_positions += 1;
    int min = mean_num_figure_positions - (mean_num_figure_positions / 2);
    int max = mean_num_figure_positions + (mean_num_figure_positions / 2);
    for (int i = 0; i < num_figures; i++)
    {
        int num_figure_positions = get_positions_value_in_matrix(matrix, 'A' + i).size();
        if (num_figure_positions < min || num_figure_positions > max) return false;
    }
    return true;
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

Figure PuzzleGenerator::get_figure_from_matrix(std::vector<std::vector<char>> &matrix, char letter)
{
    std::set<Position> figure_positions_in_matrix;
    int min_x = -1;
    int min_y = -1;
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j] == letter)
            {
                if (min_x == -1 || i < min_x) min_x = i;
                if (min_y == -1 || j < min_y) min_y = j;
                figure_positions_in_matrix.insert({i, j});
            }
        }
    }

    std::set<Position>::iterator it = figure_positions_in_matrix.begin();
    std::set<Position> figure_positions;
    while (it != figure_positions_in_matrix.end())
    {
        figure_positions.insert({it->x - min_x, it->y - min_y});
        it++;
    }

    Figure figure(letter, figure_positions);

    int num_rotations = random(0, 3);
    figure.rotate(num_rotations);

    return figure;
}