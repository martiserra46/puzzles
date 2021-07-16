#ifndef INPUT_ACTION_H
#define INPUT_ACTION_H

#include "input.h"
#include "action.h"

class Action;

class InputAction
{
    Input *input;
    Action *action;
    public:
        InputAction(Input *input, Action *action);
        virtual ~InputAction() = 0;
        void do_input_action();
};

/** MAIN MENU **/
class InputActionSelectGenerate : public InputAction
{
    public:
        InputActionSelectGenerate();
};

class InputActionDifficulty : public InputAction
{
    public:
        InputActionDifficulty();
};

class InputActionLevel : public InputAction
{
    public:
        InputActionLevel(std::string difficulty);
};

class InputActionRowsColumns : public InputAction
{
    public:
        InputActionRowsColumns();
};

class InputActionNumFigures : public InputAction
{
    public:
        InputActionNumFigures(int rows, int columns);
};

/** GAME **/
class InputActionInsertRemoveFigure : public InputAction
{
    public:
        InputActionInsertRemoveFigure(Puzzle *puzzle);
};

class InputActionFigureToInsert : public InputAction
{
    public:
        InputActionFigureToInsert(Puzzle *puzzle);
};

class InputActionFigureRotations : public InputAction
{
    public:
        InputActionFigureRotations(Puzzle *puzzle, int figure_number);
};

class InputActionFigurePosition : public InputAction
{
    public:
        InputActionFigurePosition(Puzzle *puzzle, int figure_number);
};

class InputActionFigureToRemove : public InputAction
{
    public:
        InputActionFigureToRemove(Puzzle *puzzle);
};

#endif