#ifndef ACTION_H
#define ACTION_H

#include <string>
#include "bundle.h"
#include <vector>

class Action
{
    public:
        virtual bool do_action(std::string name, Bundle bundle) = 0;
};

class ActionGroup
{
    std::vector<Action*> actions;
    public:
        bool do_action(std::string name, Bundle bundle);
};

#endif