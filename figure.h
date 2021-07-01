#ifndef FIGURE_H
#define FIGURE_H

#include <set>
#include "position.h"
#include <string>

class Figure
{
    public:
        Figure(char letter, std::set<Position> positions);
        char get_letter() const;
        std::size_t get_width() const;
        std::size_t get_height() const;
        std::set<Position> get_positions() const;
        void rotate(unsigned short num_rotations);
        bool operator==(const Figure &figure) const;
        bool operator<(const Figure &figure) const;
    private:
        char letter;
        std::size_t width;
        std::size_t height;
        std::set<Position> positions;
        void set_letter(char letter);
        void set_positions(std::set<Position> positions);
};

static int get_width_from_positions(std::set<Position> positions);
static int get_height_from_positions(std::set<Position> positions);
static int get_size_from_positions(std::set<Position> positions, int (*get_value)(Position));

#endif