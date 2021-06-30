#include "input_validator.h"
#include <string>
#include "number_utils.h"
#include "text_utils.h"

InputNumberValidator::InputNumberValidator(int min, int max)
{
    set_min_max(min, max);
}

void InputNumberValidator::set_min_max(int min, int max)
{
    this->min = min;
    this->max = max;
}

bool InputNumberValidator::is_valid(std::string input_value)
{
    if (!is_number(input_value)) return false;
    int number = std::stoi(input_value);
    if (number < min || number > max) return false;
    return true;
}

InputRowColumnValidator::InputRowColumnValidator(int min_row, int max_row, int min_col, int max_col)
{
    set_min_max_row_column(min_row, max_row, min_col, max_col);
}

void InputRowColumnValidator::set_min_max_row_column(int min_row, int max_row, int min_col, int max_col)
{
    this->min_row = min_row;
    this->max_row = max_row;
    this->min_col = min_col;
    this->max_col = max_col;
}

bool InputRowColumnValidator::is_valid(std::string input_value)
{
    std::vector<std::string> values = split(input_value, ',');
    if (values.size() != 2) return false;
    if (!is_number(values[0]) || !is_number(values[1])) return false;
    int row = std::stoi(values[0]);
    int col = std::stoi(values[1]);
    if (row < min_row || row > max_row) return false;
    if (col < min_col || col > max_col) return false;
    return true;
}