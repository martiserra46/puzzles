#ifndef TEXT_UTILS_H
#define TEXT_UTILS_H

#include <string>
#include <vector>

std::string text_before_chars(std::string text, char c, int line_width);

std::string text_after_chars(std::string text, char c, int line_width);

std::string text_between_chars(std::string text, char c, int line_width);

std::string text_between_chars(std::string text, char c_left, char c_right, int line_width);

std::string text_max_line_width(std::string text, int max_line_width);

std::string to_uppercase(std::string text);

std::vector<std::string> split(std::string text, char divider);

std::vector<std::string> to_text_lines(std::string text);

std::vector<std::string> text_line_to_text_lines(std::string text_line, std::size_t max_line_width);

#endif