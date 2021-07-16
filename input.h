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
    public:
        InputInsertRemoveFigure();
};

class InputFigureToInsert : public InputFormat
{
    Puzzle puzzle;
    public:
        InputFigureToInsert(Puzzle puzzle);
};

class InputInsertRemoveFigureWithOptions : public InputGroup
{
    public:
        InputInsertRemoveFigureWithOptions();
};

class InputFigureToInsertWithOptions : public InputGroup
{
    Puzzle puzzle;
    public:
        InputFigureToInsertWithOptions(Puzzle puzzle);
};

#endif