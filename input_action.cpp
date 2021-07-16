#include "input_action.h"
#include <string>
#include "bundle.h"
#include <utility>

/** InputAction **/
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

/** MAIN MENU **/
/** InputActionSelectGenerate **/
InputActionSelectGenerate::InputActionSelectGenerate() : InputAction(
    new InputSelectGenerateWithOptions(),
    new ActionSelectGenerateWithOptions()
) {}

/** InputActionDifficulty **/
InputActionDifficulty::InputActionDifficulty() : InputAction(
    new InputDifficultyWithOptions(),
    new ActionDifficultyWithOptions()
) {}

/** InputActionLevel **/
InputActionLevel::InputActionLevel(std::string difficulty) : InputAction(
    new InputLevelWithOptions(difficulty),
    new ActionLevelWithOptions(difficulty)
) {}

/** InputActionRowsColumns **/
InputActionRowsColumns::InputActionRowsColumns() : InputAction(
    new InputRowsColumnsWithOptions(),
    new ActionRowsColumnsWithOptions()
) {}

/** InputActionNumFigures **/
InputActionNumFigures::InputActionNumFigures(int rows, int columns) : InputAction(
    new InputNumFiguresWithOptions(rows, columns),
    new ActionNumFiguresWithOptions(rows, columns)
) {}

/** GAME **/
/** InputActionInsertRemoveFigure **/
InputActionInsertRemoveFigure::InputActionInsertRemoveFigure(Puzzle puzzle) : InputAction(
    new InputInsertRemoveFigureWithOptions(puzzle),
    new ActionInsertRemoveFigureWithOptions(puzzle)
) {}

/** InputActionFigureToInsert **/
InputActionFigureToInsert::InputActionFigureToInsert(Puzzle puzzle) : InputAction(
    new InputFigureToInsertWithOptions(puzzle),
    new ActionFigureToInsertWithOptions(puzzle)
) {}

/** InputActionFigureRotations **/
InputActionFigureRotations::InputActionFigureRotations(Puzzle puzzle, int figure_number) : InputAction(
    new InputFigureRotationsWithOptions(puzzle, figure_number),
    new ActionFigureRotationsWithOptions(puzzle, figure_number)
) {}

/** InputActionFigurePosition **/
InputActionFigurePosition::InputActionFigurePosition(Puzzle puzzle, int figure_number) : InputAction(
    new InputFigurePositionWithOptions(puzzle, figure_number),
    new ActionFigurePositionWithOptions(puzzle, figure_number)
) {}

/** InputActionFigureToRemove **/
InputActionFigureToRemove::InputActionFigureToRemove(Puzzle puzzle) : InputAction(
    new InputFigureToRemoveWithOptions(puzzle),
    new ActionFigureToRemoveWithOptions(puzzle)
) {}