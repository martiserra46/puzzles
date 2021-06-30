#include <iostream>
#include "bundle.h"

int main()
{
    Bundle bundle;
    bundle.set_string("hola", "adeu");
    bundle.set_int("num", 4);
    std::cout << bundle.get_string("hola") << " " << bundle.get_int("num") << std::endl;
    return 0;
}