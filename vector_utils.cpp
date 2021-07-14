#include "vector_utils.h"

#include <vector>

void fill_matrix(std::vector<std::vector<char>> matrix, char value)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            matrix[i][j] = value;
        }
    }
}