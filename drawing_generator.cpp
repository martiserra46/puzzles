#include "drawing_generator.h"
#include "text_utils.h"

std::string DrawingGenerator::generate_drawing(Puzzle &puzzle)
{
    std::string drawing = generate_drawing(puzzle.get_grid()) + "\n\n\n";
    drawing += generate_drawing(puzzle.get_not_placed_figures());
    return drawing;
}

std::string DrawingGenerator::generate_drawing(Grid &grid)
{
    std::string drawing;
    drawing += "     ";
    for (int i = 0; i < grid.get_width(); i++)
        drawing += " " + text_between_chars(std::to_string(i), ' ', 5);
    drawing += "\n\n";
    for (int i = 0; i < grid.get_height(); i++)
    {
        drawing += text_after_chars(std::to_string(i), ' ', 3) + "  ";
        for (int j = 0; j < grid.get_width(); j++)
        {
            drawing += "|";
            char c = grid.get_letter_from_position({j, i});
            if (c == '\0') c += ' ';
            drawing += text_between_chars(std::string(1, c), ' ', 5);
        }
        drawing += "|";
        if (i < grid.get_height() - 1) drawing += "\n\n";
        else drawing += "\n";
    }
    return drawing;
}

std::string DrawingGenerator::generate_drawing(std::vector<Figure> figures)
{
    std::string drawing = "";
    for (int i = 0; i < figures.size(); i++)
    {
        Figure &figure = figures[i];
        drawing += text_after_chars(std::to_string(i + 1), ' ', 3) + ".\n";
        drawing += generate_drawing(figure) + "\n"; 
    }
    return drawing;
}

std::string DrawingGenerator::generate_drawing(Figure &figure)
{
    std::set<Position> positions = figure.get_positions();
    std::string drawing = "";
    for (int i = 0; i < figure.get_height(); i++)
    {
        drawing += "     ";
        for (int j = 0; j < figure.get_width(); j++)
        {
            drawing += "|";
            Position position = {j, i};
            bool found = *std::find(positions.begin(), positions.end(), position) == position;
            char c = found ? figure.get_letter() : ' ';
            drawing += text_between_chars(std::string(1, c), ' ', 5);
        }
        drawing += "|";
        if (i < figure.get_height() - 1) drawing += "\n\n";
        else drawing += "\n";
    }
    return drawing;
}