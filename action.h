#ifndef ACTION_H
#define ACTION_H

#include <string>
#include "bundle.h"
#include <vector>

class Action
{
    public:
        virtual void do_action(std::string name, Bundle bundle) = 0;
};

class ActionGroup
{
    std::vector<Action*> actions;
    public:
        void do_action(std::string name, Bundle bundle);
};

#endif