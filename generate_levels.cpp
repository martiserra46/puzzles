#include "puzzle_generator.h"
#include "puzzles_file_manager.h"
#include <vector>

int main()
{
    std::vector<std::string> difficulty = {"e", "m", "h"};
    std::vector<size_t> grid_width = {5, 6, 7}, grid_height = {5, 6, 7};
    std::vector<int> num_figures = {4, 5, 6};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            Puzzle puzzle = PuzzleGenerator::generate_puzzle(grid_width[i], grid_height[i], num_figures[i]);
            PuzzlesFileManager::save_puzzle(difficulty[i], j + 1, puzzle);
        }
    }
    return 0;
}