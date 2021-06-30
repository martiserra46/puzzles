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

class InputTwoNumbersValidator : public InputValidator
{
    public:
        InputTwoNumbersValidator(int min_num_1, int max_num_1, int min_num_2, int max_num_2);
        void set_min_max_num_1_num_2(int min_num_1, int max_num_1, int min_num_2, int max_num_2);
        bool is_valid(std::string input_value);
    private:
        int min_num_1, min_num_2, max_num_1, max_num_2;
};

#endif