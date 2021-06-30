#include "input.h"
#include <iostream>
#include <string>
#include "text_utils.h"
#include <vector>

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

Bundle Input::build_bundle(std::string input_value)
{
    return Bundle();
}

InputElement::InputElement(std::string title) : title(title) {}

std::string InputElement::get_text()
{
    std::string title_to_upper = to_uppercase(title);
    std::string text = text_between_chars(title_to_upper, '-', INPUT_MAX_LINE_WIDTH) + "\n";
    text += get_text_without_title() + "\n";
    return text;
}

InputGroup::InputGroup(std::vector<Input*> list_inputs) : list_inputs(list_inputs) {}

std::string InputGroup::get_text()
{
    std::string text = "";
    for (int i = 0; i < list_inputs.size(); i++)
    {
        text += (*list_inputs[i]).get_text();
    }
    return text_max_line_width(text, INPUT_MAX_LINE_WIDTH);
}

bool InputGroup::is_valid(std::string input_value)
{
    for (int i = 0; i < list_inputs.size(); i++)
    {
        if ((*list_inputs[i]).is_valid(input_value)) return true;
    }
    return false;
}

Bundle InputGroup::build_bundle(std::string input_value)
{
    for (int i = 0; i < list_inputs.size(); i++)
    {
        Input *input = list_inputs[i];
        if ((*input).is_valid(input_value))
        {
            return input->build_bundle(input_value);
        }
    }
    return Bundle();
}

InputChoice::InputChoice(std::string title, std::vector<std::pair<std::string, std::string>> list_choices) : InputElement(title), list_choices(list_choices) {}

bool InputChoice::is_valid(std::string input_value)
{
    for (int i = 0; i < list_choices.size(); i++)
    {
        if (list_choices[i].second == input_value) return true;
    }
    return false;
}

std::string InputChoice::get_text_without_title()
{
    std::string text = "";
    for (int i = 0; i < list_choices.size(); i++)
    {
        text += list_choices[i].first + " (" + list_choices[i].second + ")\n";
    }
    return text_max_line_width(text, INPUT_MAX_LINE_WIDTH) + "\n";
}