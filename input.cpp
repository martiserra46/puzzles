#include "input.h"
#include <iostream>
#include <string>
#include "text_utils.h"
#include <vector>
#include "input_validator.h"
#include "input_converter.h"
#include <utility>
#include "number_utils.h"
#include "system_utils.h"
#include "drawing_generator.h"

#define INPUT_MAX_LINE_WIDTH 30

#define NUM_LEVELS 10

#define MIN_ROWS 4
#define MAX_ROWS 6
#define MIN_COLS 4
#define MAX_COLS 6

#define MIN_FIGURES 3
#define MAX_FIGURES 5

/** Input **/
std::pair<std::string, Bundle> Input::input()
{
    clear_screen();

    std::cout << get_top_additional_text();
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
    text += get_text_without_title();
    return text;
}

/** InputGroup **/
InputGroup::InputGroup(std::vector<Input*> list_inputs) : list_inputs(list_inputs) {}

InputGroup::~InputGroup()
{
    for (Input *input : list_inputs) delete input;
    list_inputs.clear();
}

std::string InputGroup::get_top_additional_text()
{
    std::string text;
    for (int i = 0; i < list_inputs.size(); i++)
    {
        text += list_inputs[i]->get_top_additional_text();
    }
    return text;
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

/** MAIN MENU **/
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

/** GAME **/
/** InputInsertRemoveFigure **/
InputInsertRemoveFigure::InputInsertRemoveFigure(Puzzle *puzzle) : InputChoice(
    "Insert or Remove",
    {{"Insert not placed figure", "i"}, {"Remove placed figure", "r"}}
), puzzle(puzzle) {}

std::string InputInsertRemoveFigure::get_top_additional_text()
{
    std::string drawing;
    drawing += DrawingGenerator::generate_puzzle_drawing(*puzzle) + "\n";
    return drawing;
}

bool InputInsertRemoveFigure::is_valid(std::string input_value)
{
    if (!InputChoice::is_valid(input_value)) return false;
    if (input_value == "r") return puzzle->get_placed_figures().size() > 0;
    return true;
}

/** InputFigureToInsert **/
InputFigureToInsert::InputFigureToInsert(Puzzle *puzzle) : InputFormat(
    "Figure To Insert",
    "figure-number",
    new InputNumberValidator(1, puzzle->get_const_not_placed_figures().size()),
    new InputNumberConverter("figure-number"),
    "figure-number has to be between 1 and " + std::to_string(puzzle->get_const_not_placed_figures().size()) + ".",
    "(ex: " + std::to_string(random(1, puzzle->get_const_not_placed_figures().size())) + ")"
), puzzle(puzzle) {}

std::string InputFigureToInsert::get_top_additional_text()
{
    std::string drawing;
    drawing += DrawingGenerator::generate_grid_drawing(*puzzle) + "\n";
    drawing += DrawingGenerator::generate_not_placed_figures_drawing(*puzzle) + "\n";
    return drawing;
}

/** InputFigureRotations **/
InputFigureRotations::InputFigureRotations(Puzzle *puzzle, int figure_number) : InputFormat(
    "Figure Rotations",
    "num-rotations",
    new InputNumberValidator(0, 3),
    new InputNumberConverter("num-rotations"),
    "num-rotations has to be between 0 and 3.",
    "(ex: " + std::to_string(random(0, 3)) + ")"
), puzzle(puzzle), figure_number(figure_number) {}

std::string InputFigureRotations::get_top_additional_text()
{
    std::string drawing;
    drawing += DrawingGenerator::generate_grid_drawing(*puzzle) + "\n";
    drawing += DrawingGenerator::generate_figure_drawing(*puzzle, false, figure_number) + "\n";
    return drawing;
}

/** InputFigurePosition **/
InputFigurePosition::InputFigurePosition(Puzzle *puzzle, int figure_number) : InputFormat(
    "Position To Insert",
    "row,column",
    new InputPositionToInsertFigureValidator(puzzle, figure_number),
    new InputTwoNumbersConverter("row", "column"),
    "row,column has to be a position where you can place the figure.",
    "(ex: " + std::to_string(random(0, puzzle->get_width() - 1)) + "," + std::to_string(random(0, puzzle->get_height() - 1)) + ")"
), puzzle(puzzle), figure_number(figure_number) {}

std::string InputFigurePosition::get_top_additional_text()
{
    std::string drawing;
    drawing += DrawingGenerator::generate_grid_drawing(*puzzle) + "\n";
    drawing += DrawingGenerator::generate_figure_drawing(*puzzle, false, figure_number) + "\n";
    return drawing;
}

/** InputFigureToRemove **/
InputFigureToRemove::InputFigureToRemove(Puzzle *puzzle) : InputFormat(
    "Figure To Remove",
    "figure-number",
    new InputNumberValidator(1, puzzle->get_const_placed_figures().size()),
    new InputNumberConverter("figure-number"),
    "figure-number has to be between 1 and " + std::to_string(puzzle->get_const_placed_figures().size()) + ".",
    "(ex: " + std::to_string(random(1, puzzle->get_const_placed_figures().size())) + ")"
), puzzle(puzzle) {}

std::string InputFigureToRemove::get_top_additional_text()
{
    std::string drawing;
    drawing += DrawingGenerator::generate_grid_drawing(*puzzle) + "\n";
    drawing += DrawingGenerator::generate_placed_figures_drawing(*puzzle) + "\n";
    return drawing;
}

/** InputPlayAgain **/
InputPlayAgain::InputPlayAgain(Puzzle *puzzle) : InputChoice(
    "Play again or Exit",
    {{"Play again", "play"}, {"Exit", "exit"}}
), puzzle(puzzle) {}

std::string InputPlayAgain::get_top_additional_text()
{
    std::string drawing;
    drawing += DrawingGenerator::generate_puzzle_drawing(*puzzle) + "\n";
    return drawing;
}

/** InputInsertRemoveFigureWithOptions **/
InputInsertRemoveFigureWithOptions::InputInsertRemoveFigureWithOptions(Puzzle *puzzle) : InputGroup(
    {
        new InputInsertRemoveFigure(puzzle),
        new InputExitRestart()
    }
) {}

/** InputFigureToInsertWithOptions **/
InputFigureToInsertWithOptions::InputFigureToInsertWithOptions(Puzzle *puzzle) : InputGroup(
    {
        new InputFigureToInsert(puzzle),
        new InputBack(),
        new InputExitRestart()
    }
) {}

/** InputFigureRotationsWithOptions **/
InputFigureRotationsWithOptions::InputFigureRotationsWithOptions(Puzzle *puzzle, int figure_number) : InputGroup(
    {
        new InputFigureRotations(puzzle, figure_number),
        new InputBack(),
        new InputExitRestart()
    }
) {}

/** InputFigurePositionWithOptions **/
InputFigurePositionWithOptions::InputFigurePositionWithOptions(Puzzle *puzzle, int figure_number) : InputGroup(
    {
        new InputFigurePosition(puzzle, figure_number),
        new InputBack(),
        new InputExitRestart()
    }
) {}

/** InputFigureToRemoveWithOptions **/
InputFigureToRemoveWithOptions::InputFigureToRemoveWithOptions(Puzzle *puzzle) : InputGroup(
    {
        new InputFigureToRemove(puzzle),
        new InputBack(),
        new InputExitRestart()
    }
) {}