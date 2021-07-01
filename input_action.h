#ifndef INPUT_ACTION_H
#define INPUT_ACTION_H

#include "input.h"
#include "action.h"

class Action;

class InputAction
{
    Input *input;
    Action *action;
    public:
        InputAction(Input *input, Action *action);
        virtual ~InputAction() = 0;
        void do_input_action();
};

class InputActionSelectGenerate : public InputAction
{
    public:
        InputActionSelectGenerate();
};

class InputActionDifficulty : public InputAction
{
    public:
        InputActionDifficulty();
};

class InputActionLevel : public InputAction
{
    std::string difficulty;
    public:
        InputActionLevel(std::string difficulty);
};

class InputActionRowsColumns : public InputAction
{
    public:
        InputActionRowsColumns();
};

class InputActionNumFigures : public InputAction
{
    int rows, columns;
    public:
        InputActionNumFigures(int rows, int columns);
};

#endif