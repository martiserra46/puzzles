#include <iostream>
#include "text_utils.h"

int main()
{
    std::cout << text_between_chars(to_uppercase("Hola"), '-', 30) << std::endl;
    std::cout << text_max_line_width("Ho", 4) << std::endl;
    std::cout << "a" << std::endl;
    std::cout << split("hola, em dic Martí", ' ')[0] << std::endl;
    return 0;
}