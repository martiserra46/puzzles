#include "input_converter.h"
#include <string>
#include "bundle.h"
#include "text_utils.h"

InputNumberConverter::InputNumberConverter(std::string number_name) : number_name(number_name) {}

Bundle InputNumberConverter::convert_input(std::string input_value)
{
    Bundle bundle;
    int number = std::stoi(input_value);
    bundle.set_int(number_name, number);
    return bundle;
}

InputRowColumnConverter::InputRowColumnConverter(std::string row_name, std::string column_name) : row_name(row_name), column_name(column_name) {}

Bundle InputRowColumnConverter::convert_input(std::string input_value)
{
    Bundle bundle;
    std::vector<std::string> values = split(input_value, ',');
    int row = std::stoi(values[0]);
    int col = std::stoi(values[1]);
    bundle.set_int(row_name, row);
    bundle.set_int(column_name, col);
    return bundle;
}