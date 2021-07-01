#include "input_converter.h"
#include <string>
#include "bundle.h"
#include "text_utils.h"

/** InputNumberConverter **/
InputNumberConverter::InputNumberConverter(std::string number_name) : number_name(number_name) {}

Bundle InputNumberConverter::convert_input(std::string input_value)
{
    Bundle bundle;
    int number = std::stoi(input_value);
    bundle.set_int(number_name, number);
    return bundle;
}

/** InputTwoNumbersConverter **/
InputTwoNumbersConverter::InputTwoNumbersConverter(
    std::string number_1_name, std::string number_2_name
) : number_1_name(number_1_name), number_2_name(number_2_name) {}

Bundle InputTwoNumbersConverter::convert_input(std::string input_value)
{
    Bundle bundle;
    std::vector<std::string> values = split(input_value, ',');
    int number_1 = std::stoi(values[0]);
    int number_2 = std::stoi(values[1]);
    bundle.set_int(number_1_name, number_1);
    bundle.set_int(number_2_name, number_2);
    return bundle;
}