#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

#include <vector>
#include "position.h"

void fill_matrix(std::vector<std::vector<char>> matrix, char value);

bool is_value_in_matrix(std::vector<std::vector<char>> matrix, char value);

std::vector<Position> get_positions_value_in_matrix(std::vector<std::vector<char>> matrix, char value);

#endif