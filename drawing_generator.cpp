#include "drawing_generator.h"
#include "text_utils.h"

std::string DrawingGenerator::generate_drawing(Grid &grid)
{
    std::string drawing;
    for (int i = 0; i < grid.get_height(); i++)
    {
        for (int j = 0; j < grid.get_width(); j++)
        {
            drawing += "| ";
            char letter = grid.get_letter_from_position({j, i});
            if (letter != '\0') drawing += letter;
            else drawing += " ";
            drawing += " ";
        }
        drawing += "|\n";
    }
    return drawing;
}

std::string DrawingGenerator::generate_drawing(Figure &figure)
{
    std::set<Position> positions = figure.get_positions();
    std::string drawing = "";
    for (int i = 0; i < figure.get_height(); i++)
    {
        for (int j = 0; j < figure.get_width(); j++)
        {
            drawing += "| ";
            Position position = {j, i};
            bool found = *std::find(positions.begin(), positions.end(), position) == position;
            if (found)
            {
                drawing += figure.get_letter();
            }
            else
            {
                drawing += " ";
            }
            drawing += " ";
        }
        drawing += "|\n";
    }
    return drawing;
}

std::string DrawingGenerator::generate_drawing(std::vector<Figure> figures)
{
    std::string drawing = "";
    for (int i = 0; i < figures.size(); i++)
    {
        Figure &figure = figures[i];
        drawing += "" + std::to_string(i + 1) + "." + "\n";
        drawing += generate_drawing(figure) + "\n"; 
    }
    return drawing;
}