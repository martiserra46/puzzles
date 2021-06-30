#include "input_validator.h"
#include <string>
#include "number_utils.h"

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