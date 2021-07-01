#include <iostream>
#include "grid.h"
#include "figure.h"
#include "drawing_generator.h"
#include "position.h"
#include <vector>
#include "puzzle.h"

int main()
{
    Grid grid(6, 8);
    Figure figure1('A', {{0,0},{1,0},{0,1}});
    Figure figure2('B', {{0,0}, {0,1}});
    std::set<Position> positions;
    for (int i = 0; i < 10; i++) positions.insert({i, 0});
    Figure figure3('C', positions);
    grid.insert_figure({0,0}, figure1);
    grid.insert_figure({1,1}, figure2);
    std::vector<Figure> figures = {figure1, figure2, figure3};
    Puzzle puzzle(5, 5, figures);
    DrawingGenerator drawing_generator;
    std::cout << drawing_generator.generate_drawing(puzzle) << std::endl;
    std::cout << "Hola" << std::endl;
    return 0;
}