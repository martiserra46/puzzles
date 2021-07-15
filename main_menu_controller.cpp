#include "main_menu_controller.h"
#include "puzzles_file_manager.h"
#include "puzzle_generator.h"
#include "drawing_generator.h"
#include "puzzle.h"
#include "screen.h"
#include <iostream>

void MainMenuController::play_selected_level(std::string difficulty, int level)
{
    Puzzle puzzle = PuzzlesFileManager::load_puzzle(difficulty, level);
    play_puzzle(puzzle);
}

void MainMenuController::play_generated_puzzle(int rows, int columns, int num_figures)
{
    Puzzle puzzle = PuzzleGenerator::generate_puzzle(rows, columns, num_figures);
    play_puzzle(puzzle);
}

void MainMenuController::play_puzzle(Puzzle puzzle)
{
    GameScreen game_screen(puzzle);
    game_screen.init();
}