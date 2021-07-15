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

#define NUM_LEVELS 10

#define MIN_ROWS 5
#define MAX_ROWS 10
#define MIN_COLS 5
#define MAX_COLS 10

#define MIN_FIGURES 3
#define MAX_FIGURES 10

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
InputLevel::InputLevel(std::string difficulty) : InputFormat(
    "Level",
    "level-number",
    new InputNumberValidator(1, NUM_LEVELS),
    new InputNumberConverter("level-number"),
    "level-number has to be a number between 1 and " + std::to_string(NUM_LEVELS),
    "(ex: " + std::to_string(random(1, NUM_LEVELS)) + ")"
) {
    this->difficulty = difficulty;
}

/** InputRowsColumns **/
InputRowsColumns::InputRowsColumns() : InputFormat(
    "Rows & Columns",
    "rows,columns",
    new InputTwoNumbersValidator(MIN_ROWS, MAX_ROWS, MIN_COLS, MAX_COLS),
    new InputTwoNumbersConverter("rows", "columns"),
    "rows has to be between " + std::to_string(MIN_ROWS) + " and " + std::to_string(MAX_ROWS) + ".\n" + 
    "columns has to be between " + std::to_string(MIN_COLS) + " and " + std::to_string(MAX_COLS) + ".",
    "(ex: " + std::to_string(random(MIN_ROWS, MAX_ROWS)) + "," + std::to_string(random(MIN_COLS, MAX_COLS)) + ")"
) {}

/** InputNumFigures **/
InputNumFigures::InputNumFigures(int rows, int columns) : InputFormat(
    "Num. Figures",
    "num-figures",
    new InputNumberValidator(MIN_FIGURES, MAX_FIGURES),
    new InputNumberConverter("num-figures"),
    "num-figures has to be a number between " + std::to_string(MIN_FIGURES) + " and " + std::to_string(MAX_FIGURES),
    "(ex: " + std::to_string(random(MIN_FIGURES, MAX_FIGURES)) + ")"
) {
    this->rows = rows;
    this->columns = columns;
}

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
InputLevelWithOptions::InputLevelWithOptions(std::string difficulty) : InputGroup(
    {
        new InputLevel(difficulty),
        new InputBack(),
        new InputExitRestart()
    }
) {}

/** InputRowsColumnsWithOptions **/
InputRowsColumnsWithOptions::InputRowsColumnsWithOptions() : InputGroup(
    {
        new InputRowsColumns(),
        new InputBack(),
        new InputExitRestart()
    }
) {}

/** InputNumFiguresWithOptions **/
InputNumFiguresWithOptions::InputNumFiguresWithOptions(int rows, int columns) : InputGroup(
    {
        new InputNumFigures(rows, columns),
        new InputBack(),
        new InputExitRestart()
    }
) {}