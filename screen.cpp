#include "screen.h"
#include "input_action.h"
#include "system_utils.h"

void Screen::init()
{
    clear_screen();
    display();
}

void MainMenuScreen::display()
{
    InputActionSelectGenerate input_action;
    input_action.do_input_action();
}