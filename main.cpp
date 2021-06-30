#include <iostream>
#include "input.h"
#include <utility>
#include "text_utils.h"

int main()
{
    InputNumberValidator *input_number_validator = new InputNumberValidator(5, 10);
    InputFormat input_format("Difficulty", "number", input_number_validator, "fdsafasv af dasf as fas fas fdas fas fads a fa fas fa", "dfa");
    input_format.input();
    return 0;
}