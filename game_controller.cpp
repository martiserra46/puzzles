#include "game_controller.h"
#include "drawing_generator.h"
#include <iostream>

void GameController::play(Puzzle puzzle)
{
    std::cout << DrawingGenerator::generate_puzzle_drawing(puzzle) << std::endl;
}