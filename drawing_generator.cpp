#include "drawing_generator.h"
#include "text_utils.h"

std::string DrawingGenerator::generate_drawing(const Puzzle &puzzle)
{
    std::string drawing;

    size_t title_width = puzzle.get_width() * 6 + 1;

    drawing += "\n";

    drawing += "     " + text_between_chars("___GRID___", ' ', title_width) + "\n";
    
    drawing += generate_drawing(puzzle.get_const_grid()) + "\n";

    drawing += "     " + text_between_chars("___PLACED FIGURES___", ' ', title_width) + "\n";
    std::vector<Figure> placed_figures;
    for (auto placed_figure : puzzle.get_const_placed_figures()) placed_figures.push_back(placed_figure.second);
    if (placed_figures.size() == 0) drawing += "\n  There aren't any placed figures\n\n\n";
    else drawing += generate_drawing(placed_figures) + "\n";

    drawing += "     " + text_between_chars("___NOT PLACED FIGURES___", ' ', title_width) + "\n";
    if (puzzle.get_const_not_placed_figures().size() == 0) drawing += "\n  There aren't any not placed figures\n\n\n";
    else drawing += generate_drawing(puzzle.get_const_not_placed_figures()) + "\n";
    return drawing;
}

std::string DrawingGenerator::generate_drawing(const Grid &grid)
{
    std::string drawing;
    drawing += "\n";
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
        drawing += "|\n";
    }
    drawing += "\n";
    return drawing;
}

std::string DrawingGenerator::generate_drawing(const std::vector<Figure> figures)
{
    std::string drawing;
    drawing += "\n";
    for (int i = 0; i < figures.size(); i++)
    {
        const Figure &figure = figures[i];
        drawing += text_after_chars(std::to_string(i + 1), ' ', 3) + ".\n";
        drawing += generate_drawing(figure); 
    }
    return drawing;
}

std::string DrawingGenerator::generate_drawing(const Figure &figure)
{
    std::set<Position> positions = figure.get_positions();
    std::string drawing = "";
    for (int i = 0; i < figure.get_height(); i++)
    {
        drawing += "     ";
        bool found = false;
        for (int j = 0; j < figure.get_width(); j++)
        {
            bool prev_found = found;
            Position position = {j, i};
            found = *std::find(positions.begin(), positions.end(), position) == position;
            char c = found ? figure.get_letter() : ' ';
            if (found || prev_found) drawing += "|";
            else drawing += " ";
            drawing += text_between_chars(std::string(1, c), ' ', 5);
        }
        if (found) drawing += "|";
        else drawing += " ";
        drawing += "\n";
    }
    drawing += "\n";
    return drawing;
}