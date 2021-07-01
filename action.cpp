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

ActionExitRestart::ActionExitRestart(InputAction &input_action) : input_action(input_action) {}

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
        input_action.do_input_action();
        return true;
    }
    return false;
}

bool ActionSelectGenerate::do_action(std::string name, Bundle bundle)
{
    if (name == "s")
    {
        InputActionDifficulty input_action_difficulty;
        input_action_difficulty.do_input_action();
        return true;
    }
    else if (name == "g")
    {
        InputActionRowsColumns input_action_rows_columns;
        input_action_rows_columns.do_input_action();
        return true;
    }
    return false;
}