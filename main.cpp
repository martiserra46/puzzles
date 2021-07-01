#include <iostream>
#include "grid.h"
#include "figure.h"
#include "drawing_generator.h"

int main()
{
    Grid grid(6, 8);
    Figure figure1('A', {{0,0},{1,0},{0,1}});
    Figure figure2('B', {{0,0}, {0,1}});
    grid.insert_figure({0,0}, figure1);
    grid.insert_figure({1,1}, figure2);
    DrawingGenerator drawing_generator;
    std::cout << drawing_generator.generate_drawing(grid) << std::endl;
    return 0;
}