#include <iostream>
#include "figure.h"
#include "drawing_generator.h"

int main()
{
    Figure figure('A', {{0, 0}, {1,0}});
    DrawingGenerator drawing_generator;
    std::cout << drawing_generator.generate_drawing(figure) << std::endl;
    return 0;
}