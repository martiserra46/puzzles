#ifndef INPUT_VALIDATOR_H
#define INPUT_VALIDATOR_H

class InputValidator
{
    public:
        virtual ~InputValidator() {};
        virtual bool is_valid(std::string input_value) = 0;
};

#endif