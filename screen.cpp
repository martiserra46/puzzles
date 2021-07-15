#include "screen.h"
#include "input_action.h"
#include "system_utils.h"
#include "main_menu_controller.h"
#include "game_controller.h"

void Screen::init()
{
    clear_screen();
    display();
}

void MainMenuScreen::display()
{
    InputActionSelectGenerate input_action;
    input_action.do_input_action();
}

GameScreen::GameScreen(Puzzle puzzle)
{
    this->puzzle = puzzle;
}

void GameScreen::display()
{
    GameController::play(puzzle);
}