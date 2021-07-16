#include "action.h"
#include "system_utils.h"
#include "main_menu_controller.h"
#include "drawing_generator.h"
#include <iostream>

/** ActionGroup **/
ActionGroup::ActionGroup(std::vector<Action*> actions) : actions(actions) {}

ActionGroup::~ActionGroup()
{
    for (Action *action : actions)
    {
        delete action;
    }
    actions.clear();
}

bool ActionGroup::do_action(std::string name, Bundle bundle)
{
    for (Action *action : actions)
    {
        bool result = action->do_action(name, bundle);
        if (result) return true;
    }
    return false;
}

/** ActionBack **/
ActionBack::ActionBack(InputAction *input_action) : input_action(input_action) {}

ActionBack::~ActionBack()
{
    delete input_action;
}

bool ActionBack::do_action(std::string name, Bundle bundle)
{
    if (name == "back")
    {
        clear_screen();
        input_action->do_input_action();
        return true;
    }
    return false;
}

/** ActionExit **/
bool ActionExit::do_action(std::string name, Bundle bundle)
{
    if (name != "exit") return false;
    quit();
    return true;
}

/** ActionExitRestart **/
bool ActionExitRestart::do_action(std::string name, Bundle bundle)
{
    if (name == "exit")
    {
        quit();
        return true;
    }
    else if (name == "restart")
    {
        clear_screen();
        InputActionSelectGenerate input_action;
        input_action.do_input_action();
        return true;
    }
    return false;
}

/** ActionSelectGenerate **/
bool ActionSelectGenerate::do_action(std::string name, Bundle bundle)
{
    if (name == "s")
    {
        clear_screen();
        InputActionDifficulty input_action;
        input_action.do_input_action();
        return true;
    }
    else if (name == "g")
    {
        clear_screen();
        InputActionRowsColumns input_action;
        input_action.do_input_action();
        return true;
    }
    return false;
}

/** ActionDifficulty **/
bool ActionDifficulty::do_action(std::string name, Bundle bundle)
{
    if (name == "e" || name == "m" || name == "h")
    {
        clear_screen();
        InputActionLevel input_action(name);
        input_action.do_input_action();
        return true;
    }
    return false;
}

/** ActionLevel **/
ActionLevel::ActionLevel(std::string difficulty)
{
    this->difficulty = difficulty;
}

bool ActionLevel::do_action(std::string name, Bundle bundle)
{
    if (name == "level-number")
    {
        clear_screen();
        int level = bundle.get_int("level-number");
        MainMenuController::play_selected_level(difficulty, level);
        return true;
    }
    return false;
}

/** ActionRowsColumns **/
bool ActionRowsColumns::do_action(std::string name, Bundle bundle)
{
    if (name == "rows,columns")
    {
        clear_screen();
        int rows = bundle.get_int("rows");
        int columns = bundle.get_int("columns");
        InputActionNumFigures input_action(rows, columns);
        input_action.do_input_action();
        return true;
    }
    return false;
}

/** ActionNumFigures **/
ActionNumFigures::ActionNumFigures(int rows, int columns)
{
    this->rows = rows;
    this->columns = columns;
}

bool ActionNumFigures::do_action(std::string name, Bundle bundle)
{
    if (name == "num-figures")
    {
        clear_screen();
        int num_figures = bundle.get_int("num-figures");
        MainMenuController::play_generated_puzzle(rows, columns, num_figures);
        return true;
    }
    return false;
}

/** ActionSelectGenerateWithOptions **/
ActionSelectGenerateWithOptions::ActionSelectGenerateWithOptions() : ActionGroup(
    {
        new ActionSelectGenerate(),
        new ActionExit()
    }
) {}

/** ActionDifficultyWithOptions **/
ActionDifficultyWithOptions::ActionDifficultyWithOptions() : ActionGroup(
    {
        new ActionDifficulty(),
        new ActionBack(new InputActionSelectGenerate()),
        new ActionExitRestart()
    }
) {}

/** ActionLevelWithOptions **/
ActionLevelWithOptions::ActionLevelWithOptions(std::string difficulty) : ActionGroup(
    {
        new ActionLevel(difficulty),
        new ActionBack(new InputActionDifficulty()),
        new ActionExitRestart()
    }
) {}

/** ActionRowsColumnsWithOptions **/
ActionRowsColumnsWithOptions::ActionRowsColumnsWithOptions() : ActionGroup(
    {
        new ActionRowsColumns(),
        new ActionBack(new InputActionSelectGenerate()),
        new ActionExitRestart()
    }
) {}

/** ActionNumFiguresWithOptions **/
ActionNumFiguresWithOptions::ActionNumFiguresWithOptions(int rows, int columns) : ActionGroup(
    {
        new ActionNumFigures(rows, columns),
        new ActionBack(new InputActionRowsColumns()),
        new ActionExitRestart()
    }
) {}

/** GAME **/
/** ActionInsertRemoveFigure **/
ActionInsertRemoveFigure::ActionInsertRemoveFigure(Puzzle puzzle)
{
    this->puzzle = puzzle;
}

bool ActionInsertRemoveFigure::do_action(std::string name, Bundle bundle)
{
    if (name == "i")
    {
        clear_screen();
        std::cout << std::endl;
        std::cout << DrawingGenerator::generate_grid_drawing(puzzle) << std::endl;
        std::cout << DrawingGenerator::generate_not_placed_figures_drawing(puzzle) << std::endl;
        InputActionFigureToInsert input_action(puzzle);
        input_action.do_input_action();
        return true;
    }
    else if (name == "r")
    {
        clear_screen();
        std::cout << std::endl;
        std::cout << DrawingGenerator::generate_grid_drawing(puzzle) << std::endl;
        std::cout << DrawingGenerator::generate_placed_figures_drawing(puzzle) << std::endl;
        InputActionFigureToRemove input_action(puzzle);
        input_action.do_input_action();
        return true;
    }
    return false;
}

ActionFigureToInsert::ActionFigureToInsert(Puzzle puzzle)
{
    this->puzzle = puzzle;
}

bool ActionFigureToInsert::do_action(std::string name, Bundle bundle)
{
    if (name == "figure-number")
    {
        int figure_number = bundle.get_int("figure-number") - 1;
        clear_screen();
        std::cout << std::endl;
        std::cout << DrawingGenerator::generate_grid_drawing(puzzle) << std::endl;
        std::cout << DrawingGenerator::generate_figure_drawing(puzzle, false, figure_number) << std::endl;
        InputActionFigureRotations input_action(puzzle, figure_number);
        input_action.do_input_action();
        return true;
    }
    return false;
}


ActionFigureRotations::ActionFigureRotations(Puzzle puzzle, int figure_number)
{
    this->puzzle = puzzle;
    this->figure_number = figure_number;
}

bool ActionFigureRotations::do_action(std::string name, Bundle bundle)
{
    if (name == "num-rotations")
    {
        int num_rotations = bundle.get_int("num-rotations");
        puzzle.rotate_figure(figure_number, num_rotations);
        clear_screen();
        std::cout << std::endl;
        std::cout << DrawingGenerator::generate_grid_drawing(puzzle) << std::endl;
        std::cout << DrawingGenerator::generate_figure_drawing(puzzle, false, figure_number) << std::endl;
        InputActionFigurePosition input_action(puzzle, figure_number);
        input_action.do_input_action();
        return true;
    }
    return false;
}

ActionFigurePosition::ActionFigurePosition(Puzzle puzzle, int figure_number)
{
    this->puzzle = puzzle;
    this->figure_number = figure_number;
}

bool ActionFigurePosition::do_action(std::string name, Bundle bundle)
{
    if (name == "row,column")
    {
        Position position = { bundle.get_int("row"), bundle.get_int("column") };
        puzzle.insert_figure(position, figure_number);
        clear_screen();
        return true;
    }
    return false;
}

ActionFigureToRemove::ActionFigureToRemove(Puzzle puzzle)
{
    this->puzzle = puzzle;
}

bool ActionFigureToRemove::do_action(std::string name, Bundle bundle)
{
    if (name == "figure-number")
    {
        int figure_number = bundle.get_int("figure-number") - 1;
        puzzle.remove_figure(figure_number);
        clear_screen();
        return true;
    }
    return false;
}

ActionInsertRemoveFigureWithOptions::ActionInsertRemoveFigureWithOptions(Puzzle puzzle) : ActionGroup(
    {
        new ActionInsertRemoveFigure(puzzle),
        new ActionExitRestart()
    }
) {}

ActionFigureToInsertWithOptions::ActionFigureToInsertWithOptions(Puzzle puzzle) : ActionGroup(
    {
        new ActionFigureToInsert(puzzle),
        new ActionBack(new InputActionInsertRemoveFigure(puzzle)),
        new ActionExitRestart()
    }
) {}

ActionFigureRotationsWithOptions::ActionFigureRotationsWithOptions(Puzzle puzzle, int figure_number) : ActionGroup(
    {
        new ActionFigureRotations(puzzle, figure_number),
        new ActionBack(new InputActionFigureToInsert(puzzle)),
        new ActionExitRestart()
    }
) {}

ActionFigurePositionWithOptions::ActionFigurePositionWithOptions(Puzzle puzzle, int figure_number) : ActionGroup(
    {
        new ActionFigurePosition(puzzle, figure_number),
        new ActionBack(new InputActionFigureRotations(puzzle, figure_number)),
        new ActionExitRestart()
    }
) {}

ActionFigureToRemoveWithOptions::ActionFigureToRemoveWithOptions(Puzzle puzzle) : ActionGroup(
    {
        new ActionFigureToRemove(puzzle),
        new ActionBack(new InputActionInsertRemoveFigure(puzzle)),
        new ActionExitRestart()
    }
) {}