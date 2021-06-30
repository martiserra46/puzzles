#ifndef INPUT_CONVERTER_H
#define INPUT_CONVERTER_H

#include <string>
#include "bundle.h"

class InputConverter
{
    public:
        virtual ~InputConverter() {};
        virtual Bundle convert_input(std::string input_value) = 0;
};

class InputNumberConverter : public InputConverter
{
    std::string number_name;
    public:
        InputNumberConverter(std::string number_name);
        Bundle convert_input(std::string input_value);
};

class InputTwoNumbersConverter : public InputConverter
{
    std::string number_1_name, number_2_name;
    public:
        InputTwoNumbersConverter(std::string number_1_name, std::string number_2_name);
        Bundle convert_input(std::string input_value);
};

#endif