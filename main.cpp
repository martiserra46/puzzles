#include "screen.h"
#include "puzzle_generator.h"
#include "puzzles_file_manager.h"
#include "drawing_generator.h"
#include <iostream>

int main()
{
    Puzzle puzzle = PuzzleGenerator::generate_puzzle(5, 5, 3);
    PuzzlesFileManager::save_puzzle("e", 1, puzzle);
    Puzzle puzzle2 = PuzzlesFileManager::load_puzzle("e", 1);
    std::cout << DrawingGenerator::generate_drawing(puzzle2) << std::endl;
    return 0;
}