#include "action.h"
#include <cstdlib>
#include <iostream>

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

ActionBack::ActionBack(InputAction *input_action) : input_action(input_action) {}

bool ActionBack::do_action(std::string name, Bundle bundle)
{
    if (name == "back")
    {
        input_action->do_input_action();
        return true;
    }
    return false;
}

bool ActionExit::do_action(std::string name, Bundle bundle)
{
    if (name != "exit") return false;
    system("clear");
    exit(0);
    return true;
}

bool ActionExitRestart::do_action(std::string name, Bundle bundle)
{
    if (name == "exit")
    {
        system("clear");
        exit(0);
        return true;
    }
    else if (name == "restart")
    {
        //InputActionSelectGenerate input_action;
        //input_action.do_input_action();
        return true;
    }
    return false;
}

bool ActionSelectGenerate::do_action(std::string name, Bundle bundle)
{
    if (name == "s")
    {
        // InputActionDifficulty input_action;
        // input_action.do_input_action();
        return true;
    }
    else if (name == "g")
    {
        // InputActionRowsColumns input_action;
        // input_action.do_input_action();
        return true;
    }
    return false;
}

bool ActionDifficulty::do_action(std::string name, Bundle bundle)
{
    if (name == "e" || name == "m" || name == "h")
    {
        //InputActionLevel input_action(name);
        //input_action.do_input_action();
        return true;
    }
    return false;
}

ActionLevel::ActionLevel(std::string difficulty)
{
    this->difficulty = difficulty;
}

bool ActionLevel::do_action(std::string name, Bundle bundle)
{
    if (name == "level-number")
    {
        int level = bundle.get_int("level-number");
        // GameController game_controller;
        // game_controller.play_selected_level(difficulty, level);
        return true;
    }
    return false;
}

bool ActionRowsColumns::do_action(std::string name, Bundle bundle)
{
    if (name == "rows,columns")
    {
        int rows = bundle.get_int("rows");
        int columns = bundle.get_int("columns");
        // InputActionNumFigures input_action(rows, columns);
        // input_action.do_input_action();
        return true;
    }
    return false;
}

ActionNumFigures::ActionNumFigures(int rows, int columns)
{
    this->rows = rows;
    this->columns = columns;
}

bool ActionNumFigures::do_action(std::string name, Bundle bundle)
{
    if (name == "num-figures")
    {
        int num_figures = bundle.get_int("num-figures");
        // GameController game_controller;
        // game_controller.play_generated_puzzle(rows, columns, num_figures);
        return true;
    }
    return false;
}

ActionSelectGenerateWithOptions::ActionSelectGenerateWithOptions() : ActionGroup(
    {
        new ActionSelectGenerate(),
        new ActionExit()
    }
) {}

ActionDifficultyWithOptions::ActionDifficultyWithOptions() : ActionGroup(
    {
        new ActionDifficulty(),
        //new ActionBack(new InputActionSelectGenerate()),
        new ActionExitRestart()
    }
) {}

ActionLevelWithOptions::ActionLevelWithOptions(std::string difficulty) : ActionGroup(
    {
        new ActionLevel(difficulty),
        //new ActionBack(new InputActionDifficulty());
        new ActionExitRestart()
    }
)
{
    this->difficulty = difficulty;
}

ActionRowsColumnsWithOptions::ActionRowsColumnsWithOptions() : ActionGroup(
    {
        new ActionRowsColumns(),
        //new ActionBack(new InputActionSelectGenerate()),
        new ActionExitRestart()
    }
) {}

ActionNumFiguresWithOptions::ActionNumFiguresWithOptions(int rows, int columns) : ActionGroup(
    {
        new ActionNumFigures(rows, columns),
        //new ActionBack(new InputActionRowsColumns()),
        new ActionExitRestart()
    }
) 
{
    this->rows = rows;
    this->columns = columns;
}