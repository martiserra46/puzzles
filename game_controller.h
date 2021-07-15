#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <string>
#include "puzzle.h"

class GameController
{
    public:
        void play_selected_level(std::string difficulty, int level);
        void play_generated_puzzle(int rows, int columns, int num_figures);
        void play_puzzle(Puzzle puzzle);
};

#endif