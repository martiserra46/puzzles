#include "screen.h"
#include "number_utils.h"
#include "input_action.h"
#include "puzzle_generator.h"
#include "drawing_generator.h"
#include <iostream>

int main()
{
    set_random_seed();
    
    MainMenuScreen main_menu_screen;

    main_menu_screen.init();

    return 0;
}