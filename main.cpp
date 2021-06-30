#include <iostream>
#include "input.h"
#include <utility>
#include "text_utils.h"
#include <string>
#include "bundle.h"

int main()
{
    InputRowColumnValidator *input_number_validator = new InputRowColumnValidator(5, 10, 5, 10);
    InputRowColumnConverter *input_converter = new InputRowColumnConverter("row", "column");
    InputFormat input_format("Difficulty", "row,column", input_number_validator, input_converter, "fdsafasv af dasf as fas fas fdas fas fads a fa fas fa", "dfa");
    std::pair<std::string, Bundle> result = input_format.input();
    std::cout << result.second.get_int("column") << std::endl;
    return 0;
}