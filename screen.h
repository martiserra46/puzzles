#ifndef SCREEN_H
#define SCREEN_H

class Screen
{
    public:
        void init();
    protected:
        virtual void display() = 0;
};

#endif