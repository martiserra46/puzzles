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

class InputActionSelectGenerate : public Action
{
    public:
        InputActionSelectGenerate();
};

class InputActionDifficulty : public Action
{
    public:
        InputActionDifficulty();
};

class InputActionLevel : public Action
{
    public:
        InputActionLevel();
};

class InputActionRowsColumns : public Action
{
    public:
        InputActionRowsColumns();
};

class InputActionNumFigures : public Action
{
    public:
        InputActionNumFigures();
};

#endif