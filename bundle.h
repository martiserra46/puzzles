#ifndef BUNDLE_H
#define BUNDLE_H

#include <map>
#include <string>

class Bundle
{
    std::map<std::string, std::string> strings;
    std::map<std::string, int> ints;

    public:
        void set_string(std::string, std::string);
        std::string get_string(std::string);
        void set_int(std::string, int);
        int get_int(std::string);
};

#endif