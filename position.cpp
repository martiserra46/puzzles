#include "position.h"

bool Position::operator<(const Position &position) const
{
    if (this->x != position.x) return this->x < position.x;
    return this->y < position.y;
}

bool Position::operator==(const Position &position) const
{
    return this->x == position.x && this->y == position.y;
}

Position Position::operator+(const Position &position) const
{
    return { this->x + position.x, this->y + position.y };
}