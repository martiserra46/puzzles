#include "input_validator.h"
#include <string>
#include "number_utils.h"
#include "text_utils.h"

/** InputNumberValidator **/
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

/** InputTwoNumbersValidator **/
InputTwoNumbersValidator::InputTwoNumbersValidator(int min_num_1, int max_num_1, int min_num_2, int max_num_2)
{
    set_min_max_num_1_num_2(min_num_1, max_num_1, min_num_2, max_num_2);
}

void InputTwoNumbersValidator::set_min_max_num_1_num_2(int min_num_1, int max_num_1, int min_num_2, int max_num_2)
{
    this->min_num_1 = min_num_1;
    this->max_num_1 = max_num_1;
    this->min_num_2 = min_num_2;
    this->max_num_2 = max_num_2;
}

bool InputTwoNumbersValidator::is_valid(std::string input_value)
{
    std::vector<std::string> values = split(input_value, ',');
    if (values.size() != 2) return false;
    if (!is_number(values[0]) || !is_number(values[1])) return false;
    int num_1 = std::stoi(values[0]);
    int num_2 = std::stoi(values[1]);
    if (num_1 < min_num_1 || num_1 > max_num_1) return false;
    if (num_2 < min_num_2 || num_2 > max_num_2) return false;
    return true;
}