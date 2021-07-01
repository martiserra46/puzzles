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

bool ActionExit::do_action(std::string name, Bundle bundle)
{
    if (name != "exit") return false;
    system("clear");
    exit(0);
    return true;
}