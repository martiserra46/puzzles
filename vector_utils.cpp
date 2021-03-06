#include "vector_utils.h"

#include <vector>
#include "position.h"

std::vector<std::vector<char>> create_matrix(int rows, int columns)
{
    return std::vector<std::vector<char>>(rows, std::vector<char>(columns, '\0'));
}

void fill_matrix(std::vector<std::vector<char>> &matrix, char value)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            matrix[i][j] = value;
        }
    }
}

bool is_value_in_matrix(std::vector<std::vector<char>> &matrix, char value)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j] == value) return true;
        }
    }
    return false;
}

std::vector<Position> get_positions_value_in_matrix(std::vector<std::vector<char>> &matrix, char value)
{
    std::vector<Position> positions;
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j] == value) positions.push_back({i, j}); 
        }
    }
    return positions;
}