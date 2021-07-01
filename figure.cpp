#include "figure.h"
#include <set>
#include <algorithm>
#include "position.h"
#include <string>

Figure::Figure(char letter, std::set<Position> positions) {
    set_letter(letter);
    set_positions(positions);
    width = get_width_from_positions(positions);
    height = get_height_from_positions(positions);
}

char Figure::get_letter() const
{
    return letter;
}

size_t Figure::get_width() const
{
    return width;
}

size_t Figure::get_height() const
{
    return height;
}

std::set<Position> Figure::get_positions() const
{
    return positions;
}

void Figure::rotate(unsigned short num_rotations)
{
    for (int i = 0; i < num_rotations; i++)
    {
        std::set<Position> positions = get_positions();
        std::set<Position> new_positions;
        for (std::set<Position>::iterator it = positions.begin(); it != positions.end(); it++)
        {
            Position position = *it;
            Position new_position;
            new_position.x = get_height() - 1 - position.y;
            new_position.y = position.x;
            new_positions.insert(new_position);
        }
        set_positions(new_positions);
        width = get_width_from_positions(new_positions);
        height = get_height_from_positions(new_positions);
    }
}

bool Figure::operator==(const Figure &figure) const
{
    if (get_letter() != figure.get_letter()) return false;
    if (get_positions() != figure.get_positions()) return false;
    return true;
}

bool Figure::operator<(const Figure &figure) const
{
    return get_positions().size() < figure.get_positions().size();
}

void Figure::set_letter(char letter)
{
    this->letter = letter;
}

void Figure::set_positions(std::set<Position> positions)
{
    this->positions = positions;
}

static int get_width_from_positions(std::set<Position> positions)
{
    return get_size_from_positions(positions, [](Position position) { return position.x; });
}

static int get_height_from_positions(std::set<Position> positions)
{
    return get_size_from_positions(positions, [](Position position) { return position.y; });
}

static int get_size_from_positions(std::set<Position> positions, int (*get_value)(Position))
{
    if (positions.size() == 0) return 0;
    std::set<int> values;
    for (Position position : positions) values.insert(get_value(position));
    return *(values.rbegin()) + 1;
}
