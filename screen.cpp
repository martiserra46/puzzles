#include "screen.h"
#include "input_action.h"
#include "number_utils.h"
#include "system_utils.h"

void Screen::init()
{
    set_random_seed();
    clear_screen();
    InputActionSelectGenerate input_action;
    input_action.do_input_action();
}