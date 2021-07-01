#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include "puzzle.h"
#include <string>

class LevelLoader
{
    public:
        static Puzzle load_level(std::string difficulty, int level);
};

#endif