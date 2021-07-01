#ifndef ACTION_H
#define ACTION_H

#include <string>
#include "bundle.h"

class Action
{
    public:
        virtual void do_action(std::string name, Bundle bundle) = 0;
};

#endif