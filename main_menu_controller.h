#ifndef main_menu_controller_H
#define main_menu_controller_H

#include <string>
#include "puzzle.h"

class MainMenuController
{
    public:
        static void play_selected_level(std::string difficulty, int level);
        static void play_generated_puzzle(int rows, int columns, int num_figures);
        static void play_puzzle(Puzzle puzzle);
};

#endif