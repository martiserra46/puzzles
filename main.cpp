#include <iostream>
#include "input.h"
#include <utility>

int main()
{
    InputChoice input_choice("Difficulty", {{"Easy", "e"}});
    input_choice.input();
    return 0;
}