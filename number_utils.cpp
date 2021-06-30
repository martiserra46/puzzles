#include "number_utils.h"
#include <string>
#include <cstdlib>
#include <ctime>

void set_random_seed()
{
    srand(time(0));
}

bool is_number(std::string text)
{
    if (text.length() == 0) return false;
    for (int i = 0; i < text.length(); i++)
    {
        if (!std::isdigit(text[i])) return false;
    }
    return true;
}

int random(int min, int max)
{
    return rand() % (max - min + 1) + min;
}