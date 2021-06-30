#ifndef INPUT_H
#define INPUT_H

#include <utility>
#include "bundle.h"

class Input
{
    public:
        virtual ~Input() {};
        std::pair<std::string, Bundle> input();
        virtual std::string get_text() = 0;
        virtual bool is_valid(std::string input_value) = 0;
        virtual Bundle build_bundle(std::string input_value) = 0;
};

#endif