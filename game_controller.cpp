#include "game_controller.h"
#include "level_loader.h"
#include "puzzle_generator.h"
#include "drawing_generator.h"
#include "puzzle.h"
#include <iostream>

void GameController::play_selected_level(std::string difficulty, int level)
{
    DrawingGenerator drawing_generator;
    Puzzle puzzle = LevelLoader::load_level(difficulty, level);
    std::cout << "Play selected level" << std::endl;
    std::cout << drawing_generator.generate_drawing(puzzle) << std::endl;
}

void GameController::play_generated_puzzle(int rows, int columns, int num_figures)
{
    DrawingGenerator drawing_generator;
    Puzzle puzzle = PuzzleGenerator::generate_puzzle(rows, columns, num_figures);
    std::cout << "Play selected level" << std::endl;
    std::cout << drawing_generator.generate_drawing(puzzle) << std::endl;
}