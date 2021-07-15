#ifndef SCREEN_H
#define SCREEN_H

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
    protected:
        void display();
};

#endif