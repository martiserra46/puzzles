#include "screen.h"
#include "number_utils.h"

int main()
{
    set_random_seed();
    
    MainMenuScreen main_menu_screen;

    main_menu_screen.init();
    
    return 0;
}