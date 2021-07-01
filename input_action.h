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
        ~InputAction();
        void do_input_action();
};

class InputActionSelectGenerate
{
    public:
        InputActionSelectGenerate();
};

class InputActionDifficulty
{
    public:
        InputActionDifficulty();
};

class InputActionLevel
{
    public:
        InputActionLevel();
};

class InputActionRowsColumns
{
    public:
        InputActionRowsColumns();
};

class InputActionNumFigures
{
    public:
        InputActionNumFigures();
};

#endif