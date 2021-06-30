#include "input.h"
#include <iostream>
#include <string>
#include "text_utils.h"

#define INPUT_MAX_LINE_WIDTH 30

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

InputElement::InputElement(std::string title) : title(title) {}

std::string InputElement::get_text()
{
    std::string title_to_upper = to_uppercase(title);
    std::string text = text_between_chars(title_to_upper, '-', INPUT_MAX_LINE_WIDTH) + "\n";
    text += get_text_without_title() + "\n";
    return text;
}