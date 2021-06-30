#ifndef NUMBER_UTILS_H
#define NUMBER_UTILS_H

#include <string>

void set_random_seed();

bool is_number(std::string text);

int random(int min, int max);

#endif