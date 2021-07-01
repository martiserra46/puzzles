#include "action.h"
#include <cstdlib>
#include <iostream>

ActionGroup::ActionGroup(std::vector<Action*> actions) : actions(actions) {}

bool ActionGroup::do_action(std::string name, Bundle bundle)
{
    for (Action *action : actions)
    {
        bool result = action->do_action(name, bundle);
        if (result) return true;
    }
    return false;
}

ActionBack::ActionBack(InputAction &input_action) : input_action(input_action) {}

bool ActionBack::do_action(std::string name, Bundle bundle)
{
    if (name == "back")
    {
        input_action.do_input_action();
        return true;
    }
    return false;
}

bool ActionExit::do_action(std::string name, Bundle bundle)
{
    if (name != "exit") return false;
    system("clear");
    exit(0);
    return true;
}

bool ActionExitRestart::do_action(std::string name, Bundle bundle)
{
    if (name == "exit")
    {
        system("clear");
        exit(0);
        return true;
    }
    else if (name == "restart")
    {
        //InputActionSelectGenerate input_action;
        //input_action.do_input_action();
        return true;
    }
    return false;
}

bool ActionSelectGenerate::do_action(std::string name, Bundle bundle)
{
    if (name == "s")
    {
        // InputActionDifficulty input_action;
        // input_action.do_input_action();
        return true;
    }
    else if (name == "g")
    {
        // InputActionRowsColumns input_action;
        // input_action.do_input_action();
        return true;
    }
    return false;
}