#include <iostream>
#include "input.h"
#include <utility>

int main()
{
    InputNumberValidator *input_number_validator = new InputNumberValidator(5, 10);
    InputFormat input_format("Difficulty", "number", input_number_validator, "fdsafas", "dfa");
    input_format.input();
    return 0;
}