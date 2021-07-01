#include "system_utils.h"
#include <cstdlib>

void quit()
{
    clear_screen();
    exit(0);
}

void clear_screen()
{
    system("clear");
}