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

class InputRowColumnConverter : public InputConverter
{
    std::string row_name, column_name;
    public:
        InputRowColumnConverter(std::string row_name, std::string column_name);
        Bundle convert_input(std::string input_value);
};

#endif