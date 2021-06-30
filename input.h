#ifndef INPUT_H
#define INPUT_H

#include <utility>
#include "bundle.h"

class Input
{
    public:
        std::pair<std::string, Bundle> input();
        std::string get_text();
        bool is_valid(std::string input_value);
        Bundle build_bundle(std::string input_value);
};

#endif