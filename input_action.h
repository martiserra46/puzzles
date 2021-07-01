#ifndef INPUT_ACTION_H
#define INPUT_ACTION_H

#include "input.h"
#include "action.h"

class InputAction
{
    Input *input;
    Action *action;
    public:
        InputAction(Input *input, Action *action);
        void do_input_action();
};

#endif