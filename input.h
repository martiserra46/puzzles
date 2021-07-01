#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <utility>
#include "bundle.h"
#include <vector>
#include <utility>
#include "input_validator.h"
#include "input_converter.h"

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
    public:
        InputLevel(int num_levels);
};

class InputRowsColumns : public InputFormat
{
    public:
        InputRowsColumns(int min_rows, int max_rows, int min_columns, int max_columns);
};

class InputNumFigures : public InputFormat
{
    public:
        InputNumFigures(int min, int max);
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
        InputLevelWithOptions(int num_levels);
};

class InputRowsColumnsWithOptions : public InputGroup
{
    public:
        InputRowsColumnsWithOptions(int min_rows, int max_rows, int min_columns, int max_columns);
};

class InputNumFiguresWithOptions : public InputGroup
{
    public:
        InputNumFiguresWithOptions(int min, int max);
};

#endif