#include "screen.h"
#include "number_utils.h"
#include "input_action.h"
#include "puzzle_generator.h"
#include "drawing_generator.h"
#include <iostream>

int main()
{
    set_random_seed();
    
    MainMenuScreen main_menu_screen;

    // main_menu_screen.init();
    Puzzle puzzle = PuzzleGenerator::generate_puzzle(5, 5, 5);

    std::cout << DrawingGenerator::generate_puzzle_drawing(puzzle) << std::endl;

    InputActionInsertRemoveFigure input_action(puzzle);
    input_action.do_input_action();

    std::cout << DrawingGenerator::generate_puzzle_drawing(puzzle) << std::endl;
    return 0;
}