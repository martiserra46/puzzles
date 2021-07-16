#include "drawing_generator.h"
#include "text_utils.h"

#define TEXT_LEFT_MARGIN 2
#define GRID_LEFT_MARGIN 5
#define GRID_CELL_WIDTH 5

#define NUM_LINES_SIDE_TITLE 3

std::string DrawingGenerator::generate_puzzle_drawing(const Puzzle &puzzle)
{
    std::string drawing;
    drawing += generate_grid_drawing(puzzle) + "\n";
    drawing += generate_placed_figures_drawing(puzzle) + "\n";
    drawing += generate_not_placed_figures_drawing(puzzle) + "\n";
    return drawing;
}

std::string DrawingGenerator::generate_grid_drawing(const Puzzle &puzzle)
{
    std::string drawing;

    drawing += get_formatted_title("Grid", puzzle.get_width()) + "\n";
    
    drawing += generate_drawing(puzzle.get_const_grid());

    return drawing;
}

std::string DrawingGenerator::generate_placed_figures_drawing(const Puzzle &puzzle)
{
    std::string drawing;
    
    drawing += get_formatted_title("Placed Figures", puzzle.get_width()) + "\n";
    
    std::vector<Figure> placed_figures;
    
    for (auto placed_figure : puzzle.get_const_placed_figures()) placed_figures.push_back(placed_figure.second);
    
    if (placed_figures.size() == 0) drawing += "\nThere aren't any placed figures\n\n";
    else drawing += generate_drawing(placed_figures);

    return drawing;
}

std::string DrawingGenerator::generate_not_placed_figures_drawing(const Puzzle &puzzle)
{
    std::string drawing;

    drawing += get_formatted_title("Not Placed Figures", puzzle.get_width()) + "\n";

    if (puzzle.get_const_not_placed_figures().size() == 0) drawing += "\nThere aren't any not placed figures\n";
    else drawing += generate_drawing(puzzle.get_const_not_placed_figures());

    return drawing;
}

std::string DrawingGenerator::generate_figure_drawing(const Puzzle &puzzle, bool placed, int figure_number)
{
    Figure figure = placed ? puzzle.get_const_placed_figures()[figure_number].second : puzzle.get_const_not_placed_figures()[figure_number];
    std::string drawing = generate_drawing(figure);
    return drawing;
}

std::string DrawingGenerator::generate_drawing(const Grid &grid)
{
    std::string drawing;
    drawing += "\n";
    drawing += std::string(GRID_LEFT_MARGIN, ' ');
    for (int i = 0; i < grid.get_width(); i++)
        drawing += " " + text_between_chars(std::to_string(i), ' ', GRID_CELL_WIDTH);
    drawing += "\n\n";
    for (int i = 0; i < grid.get_height(); i++)
    {
        drawing += text_after_chars(std::to_string(i), ' ', TEXT_LEFT_MARGIN + 1) + std::string(GRID_LEFT_MARGIN - TEXT_LEFT_MARGIN - 1, ' ');
        for (int j = 0; j < grid.get_width(); j++)
        {
            drawing += "|";
            char c = grid.get_letter_from_position({j, i});
            if (c == '\0') c += ' ';
            drawing += text_between_chars(std::string(1, c), ' ', GRID_CELL_WIDTH);
        }
        drawing += "|\n\n";
    }
    return drawing;
}

std::string DrawingGenerator::generate_drawing(const std::vector<Figure> figures)
{
    std::string drawing;
    drawing += "\n";
    for (int i = 0; i < figures.size(); i++)
    {
        const Figure &figure = figures[i];
        drawing += text_after_chars(std::to_string(i + 1), ' ', TEXT_LEFT_MARGIN + 1) + ".\n\n";
        drawing += generate_drawing(figure) + "\n\n";
    }
    return drawing;
}

std::string DrawingGenerator::generate_drawing(const Figure &figure)
{
    std::set<Position> positions = figure.get_positions();
    std::string drawing = "";
    drawing += std::string(GRID_LEFT_MARGIN, ' ');
    for (int i = 0; i < figure.get_width(); i++)
        drawing += " " + text_between_chars(std::to_string(i), ' ', GRID_CELL_WIDTH);
    drawing += "\n\n";
    for (int i = 0; i < figure.get_height(); i++)
    {
        drawing += text_after_chars(std::to_string(i), ' ', TEXT_LEFT_MARGIN + 1) + std::string(GRID_LEFT_MARGIN - TEXT_LEFT_MARGIN - 1, ' ');
        bool found = false;
        for (int j = 0; j < figure.get_width(); j++)
        {
            bool prev_found = found;
            Position position = {j, i};
            found = *std::find(positions.begin(), positions.end(), position) == position;
            char c = found ? figure.get_letter() : ' ';
            if (found || prev_found) drawing += "|";
            else drawing += " ";
            drawing += text_between_chars(std::string(1, c), ' ', GRID_CELL_WIDTH);
        }
        if (found) drawing += "|";
        else drawing += " ";
        drawing += "\n\n";
    }
    return drawing;
}

std::string DrawingGenerator::get_formatted_title(std::string title, size_t puzzle_width)
{
    size_t title_width = GRID_LEFT_MARGIN + puzzle_width * (GRID_CELL_WIDTH + 1) + 1;
    title = to_uppercase(title);
    title = text_between_chars(title, '-', title_width);
    return title;
}