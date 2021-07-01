#include "input_action.h"
#include <string>
#include "bundle.h"
#include <utility>

InputAction::InputAction(Input *input, Action *action) : input(input), action(action) {}

InputAction::~InputAction()
{
    delete input;
    delete action;
}

void InputAction::do_input_action()
{
    std::pair<std::string, Bundle> input_value = input->input();
    action->do_action(input_value.first, input_value.second);
}

InputActionSelectGenerate::InputActionSelectGenerate() : InputAction(
    {
        new InputSelectGenerateWithOptions(),
        new ActionSelectGenerateWithOptions()
    }
) {}

InputActionDifficulty::InputActionDifficulty() : InputAction(
    {
        new InputDifficultyWithOptions(),
        new ActionDifficultyWithOptions()
    }
) {}

InputActionLevel::InputActionLevel(std::string difficulty) : InputAction(
    {
        new InputLevelWithOptions(difficulty),
        new ActionLevelWithOptions(difficulty)
    }
)
{
    this->difficulty = difficulty;
}

InputActionRowsColumns::InputActionRowsColumns() : InputAction(
    {
        new InputRowsColumnsWithOptions(),
        new ActionRowsColumnsWithOptions()
    }
) {}

InputActionNumFigures::InputActionNumFigures(int rows, int columns) : InputAction(
    {
        new InputNumFiguresWithOptions(rows, columns),
        new ActionNumFiguresWithOptions(rows, columns)
    }
)
{
    this->rows = rows;
    this->columns = columns;
}