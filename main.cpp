#include "screen.h"
#include "number_utils.h"
#include "input.h"
#include "puzzle_generator.h"
#include "drawing_generator.h"
#include <iostream>

int main()
{
    set_random_seed();
    
    MainMenuScreen main_menu_screen;

    // main_menu_screen.init();
    Puzzle puzzle = PuzzleGenerator::generate_puzzle(5, 5, 5);
    //std::cout << DrawingGenerator::generate_drawing(puzzle) << std::endl;
    InputFigureToInsertWithOptions input(puzzle);
    input.input();

    return 0;
}