#include <iostream>
#include "input.h"
#include <utility>
#include "text_utils.h"
#include <string>
#include "bundle.h"

int main()
{
    InputRowsColumns input_exit(5, 10, 5, 10);
    input_exit.input();
    return 0;
}