#include "screen.h"
#include "number_utils.h"
#include "input.h"

int main()
{
    set_random_seed();
    
    MainMenuScreen main_menu_screen;

    // main_menu_screen.init();
    
    InputInsertRemoveFigureWithOptions input;
    input.input();

    return 0;
}