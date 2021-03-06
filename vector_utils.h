#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

#include <vector>
#include "position.h"

std::vector<std::vector<char>> create_matrix(int rows, int columns);

void fill_matrix(std::vector<std::vector<char>> &matrix, char value);

bool is_value_in_matrix(std::vector<std::vector<char>> &matrix, char value);

std::vector<Position> get_positions_value_in_matrix(std::vector<std::vector<char>> &matrix, char value);

#endif