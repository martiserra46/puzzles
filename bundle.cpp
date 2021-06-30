#include "bundle.h"
#include <map>
#include <string>

void Bundle::set_string(std::string key, std::string value)
{
    strings.insert(std::pair<std::string, std::string>(key, value));
}

std::string Bundle::get_string(std::string key)
{
    return strings.at(key);
}

void Bundle::set_int(std::string key, int value)
{
    ints.insert(std::pair<std::string, int>(key, value));
}

int Bundle::get_int(std::string key)
{
    return ints.at(key);
}