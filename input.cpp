#include "input.h"
#include <iostream>
#include <string>

std::pair<std::string, Bundle> Input::input()
{
    std::cout << get_text();

    std::string input_value;
    bool valid;
    do
    {
        std::cout << ">> ";
        std::getline(std::cin, input_value);
        valid = is_valid(input_value);
        if (!valid)
        {
            std::cout << "Invalid input" << std::endl;
        }
    }
    while (!valid);

    std::cout << std::endl;

    Bundle bundle = build_bundle(input_value);

    return std::pair<std::string, Bundle>(input_value, bundle);
}
