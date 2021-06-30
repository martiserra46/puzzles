#include <iostream>
#include "number_utils.h"

int main()
{
    set_random_seed();
    std::cout << random(1,5) << std::endl;
    std::cout << is_number("43") << std::endl;
    std::cout << is_number("fda") << std::endl;
    return 0;
}