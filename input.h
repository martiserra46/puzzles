#ifndef INPUT_H
#define INPUT_H

#include <utility>
#include "bundle.h"
#include <vector>

class Input
{
    public:
        virtual ~Input() {};
        std::pair<std::string, Bundle> input();
        virtual std::string get_text() = 0;
        virtual bool is_valid(std::string input_value) = 0;
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
    public:
        InputGroup(std::vector<Input*> list_inputs);
        std::string get_text();
        bool is_valid(std::string input_value);
        Bundle build_bundle(std::string input_value);
    private:
        std::vector<Input*> list_inputs;
};

class InputChoice : public InputElement
{
    public:
        InputChoice(std::string title, std::vector<std::pair<std::string, std::string>> list_choices);
        bool is_valid(std::string value);
    protected:
        std::string get_text_without_title();
    private:
        std::vector<std::pair<std::string, std::string>> list_choices;
};

#endif