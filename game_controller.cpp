#include "game_controller.h"
#include "drawing_generator.h"
#include <iostream>
#include "system_utils.h"
#include "input_action.h"

void GameController::play(Puzzle puzzle)
{
    while (puzzle.get_not_placed_figures().size() > 0)
    {
        InputActionInsertRemoveFigure input_action(&puzzle);
        input_action.do_input_action();
    }
    InputActionPlayAgain input_action(&puzzle);
    input_action.do_input_action();
}