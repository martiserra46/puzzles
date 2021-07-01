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
    public:
        InputActionLevel();
};

class InputActionRowsColumns : public InputAction
{
    public:
        InputActionRowsColumns();
};

class InputActionNumFigures : public InputAction
{
    public:
        InputActionNumFigures();
};

#endif