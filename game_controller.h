#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <string>

class GameController
{
    public:
        void play_selected_level(std::string difficulty, int level);
        void play_generated_puzzle(int rows, int columns, int num_figures);
};

#endif