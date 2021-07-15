#ifndef POSITION_H
#define POSITION_H

struct Position {
    int x, y;
    bool operator<(const Position &position) const;
    bool operator==(const Position &position) const;
    Position operator+(const Position &position) const;
    Position operator-(const Position &position) const;
};

#endif