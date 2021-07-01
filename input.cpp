#include "input.h"
#include <iostream>
#include <string>
#include "text_utils.h"
#include <vector>
#include "input_validator.h"
#include "input_converter.h"
#include <utility>
#include "number_utils.h"

#define INPUT_MAX_LINE_WIDTH 30

/** Input **/
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

    std::string name = build_name(input_value);
    Bundle bundle = build_bundle(input_value);

    return std::pair<std::string, Bundle>(name, bundle);
}

std::string Input::build_name(std::string input_value)
{
    return input_value;
}

Bundle Input::build_bundle(std::string input_value)
{
    return Bundle();
}

/** InputElement **/
InputElement::InputElement(std::string title) : title(title) {}

std::string InputElement::get_text()
{
    std::string title_to_upper = to_uppercase(title);
    std::string text = text_between_chars(title_to_upper, '-', INPUT_MAX_LINE_WIDTH) + "\n";
    text += get_text_without_title() + "\n";
    return text;
}

/** InputGroup **/
InputGroup::InputGroup(std::vector<Input*> list_inputs) : list_inputs(list_inputs) {}

InputGroup::~InputGroup()
{
    for (Input *input : list_inputs) delete input;
    list_inputs.clear();
}

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

std::string InputGroup::build_name(std::string input_value)
{
    for (int i = 0; i < list_inputs.size(); i++)
    {
        Input *input = list_inputs[i];
        if ((*input).is_valid(input_value))
        {
            return input->build_name(input_value);
        }
    }
    return input_value;
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

/** InputChoice **/
InputChoice::InputChoice(
    std::string title,
    std::vector<std::pair<std::string, std::string>> list_choices
) : InputElement(title), list_choices(list_choices) {}

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

/** InputFormat **/
InputFormat::InputFormat(
    std::string title,
    std::string format,
    InputValidator *input_validator,
    InputConverter *input_converter,
    std::string description,
    std::string example
) : InputElement(title), format(format), input_validator(input_validator), input_converter(input_converter), description(description), example(example) {}

InputFormat::~InputFormat()
{
    delete input_validator;
    delete input_converter;
}

std::string InputFormat::get_text_without_title()
{
    std::string text = ">> " + format + "\n";
    text += "\n";
    text += description + "\n";
    text += "\n";
    text += example + "\n";
    return text_max_line_width(text, INPUT_MAX_LINE_WIDTH) + "\n";
}

bool InputFormat::is_valid(std::string input_value)
{
    return input_validator->is_valid(input_value);
}

std::string InputFormat::build_name(std::string input_value)
{
    return format;
}

Bundle InputFormat::build_bundle(std::string input_value)
{
    return input_converter->convert_input(input_value);
}

/** InputBack **/
InputBack::InputBack() : InputChoice("Back", {{"Back", "back"}}) {}

/** InputExit **/
InputExit::InputExit() : InputChoice("Exit", {{"Exit", "exit"}}) {}

/** InputExitRestart **/
InputExitRestart::InputExitRestart() : InputChoice("Options", {{"Exit", "exit"}, {"Restart", "restart"}}) {}

/** InputSelectGenerate **/
InputSelectGenerate::InputSelectGenerate() : InputChoice(
    "Select or Generate",
    {{"Select existing puzzle", "s"}, {"Generate puzzle", "g"}}
) {}

/** InputDifficulty **/
InputDifficulty::InputDifficulty() : InputChoice(
    "Difficulty",
    {{"Easy", "e"}, {"Medium", "m"}, {"Hard", "h"}}
) {}

/** InputLevel **/
InputLevel::InputLevel(int num_levels) : InputFormat(
    "Level",
    "level-number",
    new InputNumberValidator(1, num_levels),
    new InputNumberConverter("level-number"),
    "level-number has to be a number between 1 and " + std::to_string(num_levels),
    "(ex: " + std::to_string(random(1, num_levels)) + ")"
) {}

/** InputRowsColumns **/
InputRowsColumns::InputRowsColumns(int min_rows, int max_rows, int min_columns, int max_columns) : InputFormat(
    "Rows & Columns",
    "rows,columns",
    new InputTwoNumbersValidator(min_rows, max_rows, min_columns, max_columns),
    new InputTwoNumbersConverter("rows", "columns"),
    "rows has to be between " + std::to_string(min_rows) + " and " + std::to_string(max_rows) + ".\n" + 
    "columns has to be between " + std::to_string(min_columns) + " and " + std::to_string(max_columns) + ".",
    "(ex: " + std::to_string(random(min_rows, max_rows)) + "," + std::to_string(random(min_columns, max_columns)) + ")"
) {}

/** InputNumFigures **/
InputNumFigures::InputNumFigures(int min, int max) : InputFormat(
    "Num. Figures",
    "num-figures",
    new InputNumberValidator(min, max),
    new InputNumberConverter("num-figures"),
    "num-figures has to be a number between " + std::to_string(min) + " and " + std::to_string(max),
    "(ex: " + std::to_string(random(min, max)) + ")"
) {}

/** InputSelectGenerateWithOptions **/
InputSelectGenerateWithOptions::InputSelectGenerateWithOptions() : InputGroup(
    {
        new InputSelectGenerate(),
        new InputExit()
    }
) {}

/** InputDifficultyWithOptions **/
InputDifficultyWithOptions::InputDifficultyWithOptions() : InputGroup(
    {
        new InputDifficulty(),
        new InputBack(),
        new InputExitRestart()
    }
) {}

/** InputLevelWithOptions **/
InputLevelWithOptions::InputLevelWithOptions(int num_levels) : InputGroup(
    {
        new InputLevel(num_levels),
        new InputBack(),
        new InputExitRestart()
    }
) {}

/** InputRowsColumnsWithOptions **/
InputRowsColumnsWithOptions::InputRowsColumnsWithOptions(int min_rows, int max_rows, int min_columns, int max_columns) : InputGroup(
    {
        new InputRowsColumns(min_rows, max_rows, min_columns, max_columns),
        new InputBack(),
        new InputExitRestart()
    }
) {}

/** InputNumFiguresWithOptions **/
InputNumFiguresWithOptions::InputNumFiguresWithOptions(int min, int max) : InputGroup(
    {
        new InputNumFigures(min, max),
        new InputBack(),
        new InputExitRestart()
    }
) {}