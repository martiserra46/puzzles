#include "screen.h"
#include "puzzles_file_manager.h"
#include <iostream>

int main()
{
    Grid grid(4, 4);
    Figure figure('A', {{0,0}, {1,0}});
    Figure figure2('B', {{0,0}});
    grid.insert_figure({0,0}, figure);
    grid.insert_figure({0,1}, figure2);
    std::cout << grid << std::endl;
    Grid grid2(0,0);
    std::cin >> grid2;
    std::cout << grid2 << std::endl;
    return 0;
}