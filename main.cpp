#include "screen.h"
#include "puzzles_file_manager.h"
#include <iostream>

int main()
{
    Figure figure('A', {{0,0}, {1,0}});
    Figure figure2('B', {{0,0}});
    Puzzle puzzle(4, 4, {figure, figure2});

    puzzle.insert_figure({0,0}, 0);
    
    std::cout << puzzle << std::endl;
    

    return 0;
}