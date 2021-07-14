#include "screen.h"
#include "number_utils.h"
#include "puzzle_generator.h"
#include "vector_utils.h"
#include <iostream>
#include "puzzle.h"
#include "figure.h"
#include "drawing_generator.h"

int main()
{
    set_random_seed();
    DrawingGenerator drawing_generator;
    Puzzle puzzle = PuzzleGenerator::generate_puzzle(6, 8, 4);
    std::cout << drawing_generator.generate_drawing(puzzle.get_grid()) << std::endl;
    std::cout << drawing_generator.generate_drawing(puzzle.get_not_placed_figures()) << std::endl;
    return 0;
}