#ifndef ACTION_H
#define ACTION_H

#include <string>
#include "bundle.h"
#include <vector>
#include "input_action.h"

class InputAction;

class Action
{
    public:
        virtual ~Action() {};
        virtual bool do_action(std::string name, Bundle bundle) = 0;
};

class ActionGroup
{
    std::vector<Action*> actions;
    public:
        ActionGroup(std::vector<Action*> actions);
        bool do_action(std::string name, Bundle bundle);
};

class ActionBack
{
    InputAction &input_action;
    public:
        ActionBack(InputAction &input_action);
        bool do_action(std::string name, Bundle bundle);
};

class ActionExit
{
    public:
        bool do_action(std::string name, Bundle bundle);
};

class ActionExitRestart
{
    InputAction &input_action;
    public:
        ActionExitRestart(InputAction &input_action);
        bool do_action(std::string name, Bundle bundle);
};

#endif