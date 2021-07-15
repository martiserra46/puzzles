#ifndef SCREEN_H
#define SCREEN_H

#include "puzzle.h"

class Screen
{
    public:
        void init();
    protected:
        virtual void display() = 0;
};

class MainMenuScreen : public Screen
{
    protected:
        void display();
};

class GameScreen : public Screen
{
    public:
        GameScreen(Puzzle puzzle);
    protected:
        void display();
    private:
        Puzzle puzzle;
};

#endif