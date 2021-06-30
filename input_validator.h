#ifndef INPUT_VALIDATOR_H
#define INPUT_VALIDATOR_H

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

#endif