#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <utility>
#include "bundle.h"
#include <vector>
#include <utility>
#include "input_validator.h"
#include "input_converter.h"
#include "puzzle.h"

class Input
{
    public:
        virtual ~Input() {};
        std::pair<std::string, Bundle> input();
        virtual std::string get_top_additional_text() { return ""; };
        virtual std::string get_text() = 0;
        virtual bool is_valid(std::string input_value) = 0;
        virtual std::string build_name(std::string input_value);
        virtual Bundle build_bundle(std::string input_value);
};

class InputElement : public Input
{
    std::string title;
    public:
        InputElement(std::string title);
        std::string get_text();
    protected:
        virtual std::string get_text_without_title() = 0;
};

class InputGroup : public Input
{
    std::vector<Input*> list_inputs;
    public:
        InputGroup(std::vector<Input*> list_inputs);
        ~InputGroup();
        std::string get_top_additional_text();
        std::string get_text();
        bool is_valid(std::string input_value);
        std::string build_name(std::string input_value);
        Bundle build_bundle(std::string input_value);
};

class InputChoice : public InputElement
{
    std::vector<std::pair<std::string, std::string>> list_choices;
    public:
        InputChoice(std::string title, std::vector<std::pair<std::string, std::string>> list_choices);
        bool is_valid(std::string input_value);
    protected:
        std::string get_text_without_title();
};

class InputFormat : public InputElement
{
    std::string format;
    InputValidator *input_validator;
    InputConverter *input_converter;
    std::string description;
    std::string example;
    public:
        InputFormat(std::string title, std::string format, InputValidator *input_validator, InputConverter *input_converter, std::string description, std::string example);
        ~InputFormat();
        bool is_valid(std::string input_value);
        std::string build_name(std::string input_value);
        Bundle build_bundle(std::string input_value);
    protected:
        std::string get_text_without_title();
};

class InputBack : public InputChoice
{
    public:
        InputBack();
};

class InputExit : public InputChoice
{
    public:
        InputExit();
};

class InputExitRestart : public InputChoice
{
    public:
        InputExitRestart();
};

/** MAIN MENU **/
class InputSelectGenerate : public InputChoice
{
    public:
        InputSelectGenerate();
};

class InputDifficulty : public InputChoice
{
    public:
        InputDifficulty();
};

class InputLevel : public InputFormat
{
    std::string difficulty;
    public:
        InputLevel(std::string difficulty);
};

class InputRowsColumns : public InputFormat
{
    public:
        InputRowsColumns();
};

class InputNumFigures : public InputFormat
{
    int rows, columns;
    public:
        InputNumFigures(int rows, int columns);
};

class InputSelectGenerateWithOptions : public InputGroup
{
    public:
        InputSelectGenerateWithOptions();
};

class InputDifficultyWithOptions : public InputGroup
{
    public:
        InputDifficultyWithOptions();
};

class InputLevelWithOptions : public InputGroup
{
    public:
        InputLevelWithOptions(std::string difficulty);
};

class InputRowsColumnsWithOptions : public InputGroup
{
    public:
        InputRowsColumnsWithOptions();
};

class InputNumFiguresWithOptions : public InputGroup
{
    public:
        InputNumFiguresWithOptions(int rows, int columns);
};


/** GAME **/
class InputInsertRemoveFigure : public InputChoice
{
    Puzzle *puzzle;
    public:
        InputInsertRemoveFigure(Puzzle *puzzle);
        std::string get_top_additional_text();
        bool is_valid(std::string input_value);
};

class InputFigureToInsert : public InputFormat
{
    Puzzle *puzzle;
    public:
        InputFigureToInsert(Puzzle *puzzle);
        std::string get_top_additional_text();
};

class InputFigureRotations : public InputFormat
{
    Puzzle *puzzle;
    int figure_number;
    public:
        InputFigureRotations(Puzzle *puzzle, int figure_number);
        std::string get_top_additional_text();
};

class InputFigurePosition : public InputFormat
{
    Puzzle *puzzle;
    int figure_number;
    public:
        InputFigurePosition(Puzzle *puzzle, int figure_number);
        std::string get_top_additional_text();
};

class InputFigureToRemove : public InputFormat
{
    Puzzle *puzzle;
    public:
        InputFigureToRemove(Puzzle *puzzle);
        std::string get_top_additional_text();
};

class InputPlayAgain : public InputChoice
{
    Puzzle *puzzle;
    public:
        InputPlayAgain(Puzzle *puzzle);
        std::string get_top_additional_text();
};

class InputInsertRemoveFigureWithOptions : public InputGroup
{
    public:
        InputInsertRemoveFigureWithOptions(Puzzle *puzzle);
};

class InputFigureToInsertWithOptions : public InputGroup
{
    Puzzle *puzzle;
    public:
        InputFigureToInsertWithOptions(Puzzle *puzzle);
};

class InputFigureRotationsWithOptions : public InputGroup
{
    public:
        InputFigureRotationsWithOptions(Puzzle *puzzle, int figure_number);
};

class InputFigurePositionWithOptions : public InputGroup
{
    Puzzle *puzzle;
    int figure_number;
    public:
        InputFigurePositionWithOptions(Puzzle *puzzle, int figure_number);
};

class InputFigureToRemoveWithOptions : public InputGroup
{
    Puzzle *puzzle;
    public:
        InputFigureToRemoveWithOptions(Puzzle *puzzle);
};

#endif