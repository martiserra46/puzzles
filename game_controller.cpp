#include "game_controller.h"
#include "puzzles_file_manager.h"
#include "puzzle_generator.h"
#include "drawing_generator.h"
#include "puzzle.h"
#include <iostream>

void GameController::play_selected_level(std::string difficulty, int level)
{
    Puzzle puzzle = PuzzlesFileManager::load_puzzle(difficulty, level);
    std::cout << DrawingGenerator::generate_drawing(puzzle) << std::endl;
}

void GameController::play_generated_puzzle(int rows, int columns, int num_figures)
{
    Puzzle puzzle = PuzzleGenerator::generate_puzzle(rows, columns, num_figures);
    std::cout << DrawingGenerator::generate_drawing(puzzle) << std::endl;
}

void GameController::play_puzzle(Puzzle puzzle)
{

}