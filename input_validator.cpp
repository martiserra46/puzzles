#include "input_validator.h"
#include <string>
#include "number_utils.h"
#include "text_utils.h"
#include "bundle.h"
#include "input_converter.h"

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

/** InputPositionToInsertFigureValidator **/
InputPositionToInsertFigureValidator::InputPositionToInsertFigureValidator(Puzzle puzzle, int figure_number)
{
    set_puzzle_figure_number(puzzle, figure_number);
}

void InputPositionToInsertFigureValidator::set_puzzle_figure_number(Puzzle puzzle, int figure_number)
{
    this->puzzle = puzzle;
    this->figure_number = figure_number;
}

bool InputPositionToInsertFigureValidator::is_valid(std::string input_value)
{
    InputTwoNumbersValidator input_two_numbers_validator(0, puzzle.get_width() - 1, 0, puzzle.get_height() - 1);
    if (!input_two_numbers_validator.is_valid(input_value)) return false;
    InputTwoNumbersConverter input_two_numbers_converter("row", "column");
    Bundle bundle = input_two_numbers_converter.convert_input(input_value);
    Position position = { bundle.get_int("row"), bundle.get_int("column") };
    return puzzle.can_insert_figure(position, figure_number);
}