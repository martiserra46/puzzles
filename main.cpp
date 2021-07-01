#include <iostream>
#include "action.h"
#include <string>
#include "bundle.h"

int main()
{
    ActionExit action_exit;
    action_exit.do_action("eit", Bundle());
    std::cout << "Hola" << std::endl;
    return 0;
}