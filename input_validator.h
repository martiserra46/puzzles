#ifndef INPUT_VALIDATOR_H
#define INPUT_VALIDATOR_H

#include <string>

class InputValidator
{
    public:
        virtual ~InputValidator() {};
        virtual bool is_valid(std::string input_value) = 0;
};

class InputNumberValidator : public InputValidator
{
    public:
        InputNumberValidator(int min, int max);
        void set_min_max(int min, int max);
        bool is_valid(std::string input_value);
    private:
        int min, max;
};

class InputRowColumnValidator : public InputValidator
{
    public:
        InputRowColumnValidator(int min_row, int max_row, int min_col, int max_col);
        void set_min_max_row_column(int min_row, int max_row, int min_col, int max_col);
        bool is_valid(std::string input_value);
    private:
        int min_row, min_col, max_row, max_col;
};

#endif