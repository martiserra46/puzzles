#include "text_utils.h"
#include <string>
#include <vector>
#include <sstream>

std::string text_before_chars(std::string text, char c, int line_width)
{
    std::string formatted_text = "";
    int num_chars = line_width - text.length();
    formatted_text += text;
    for (int i = 0; i < num_chars; i++) formatted_text += c;
    return formatted_text;
}

std::string text_after_chars(std::string text, char c, int line_width)
{
    std::string formatted_text = "";
    int num_chars = line_width - text.length();
    for (int i = 0; i < num_chars; i++) formatted_text += c;
    formatted_text += text;
    return formatted_text;
}

std::string text_between_chars(std::string text, char c, int line_width)
{
    return text_between_chars(text, c, c, line_width);
}

std::string text_between_chars(std::string text, char c_left, char c_right, int line_width)
{
    std::string formatted_text = "";
    int left_chars = (line_width - text.length() - 2) / 2;
    int right_chars = left_chars;
    if ((line_width - text.length() - 2) % 2 == 1) right_chars += 1;
    for (int i = 0; i < left_chars; i++) formatted_text += c_left;
    formatted_text += " " + text + " ";
    for (int i = 0; i < right_chars; i++) formatted_text += c_right;
    return formatted_text;
}

std::string text_max_line_width(std::string text, int max_line_width)
{
    std::vector<std::string> text_lines = to_text_lines(text);
    std::vector<std::string> result_lines;
    std::string result = "";
    for (std::string text_line : text_lines)
    {
        std::vector<std::string> result_text_line = text_line_to_text_lines(text_line, max_line_width);
        result_lines.insert(result_lines.end(), result_text_line.begin(), result_text_line.end());
    }
    for (std::string line : result_lines) result += line + "\n";
    return result;
}

std::string to_uppercase(std::string text)
{
    for (int i = 0; i < text.size(); i++)
    {
        text[i] = std::toupper(text[i]);
    }
    return text;
}

std::vector<std::string> split(std::string text, char divider)
{
    std::vector<std::string> result;
    std::stringstream text_stream(text);
    std::string segment;
    while (getline(text_stream, segment, divider))
    {
        result.push_back(segment);
    }
    return result;
}

std::vector<std::string> to_text_lines(std::string text)
{
    std::vector<std::string> result;
    std::size_t next_line_char_index;
    do
    {
        next_line_char_index = text.find("\n", 0);
        if (next_line_char_index == std::string::npos)
        {
            result.push_back(text);
            text = "";
        }
        else
        {
            result.push_back(text.substr(0, next_line_char_index));
            text.erase(0, next_line_char_index + 1);
        }
    }
    while (text.size() > 0);
    return result;
}

std::vector<std::string> text_line_to_text_lines(std::string text_line, std::size_t max_line_width)
{
    std::vector<std::string> result;
    std::size_t last_line_pos;
    do
    {
        if (text_line.size() <= max_line_width)
        {
            result.push_back(text_line);
            text_line = "";
            break;
        }
        last_line_pos = text_line.rfind(" ", max_line_width);
        if (last_line_pos == std::string::npos) last_line_pos = max_line_width - 1;
        result.push_back(text_line.substr(0, last_line_pos));
        text_line.erase(0, last_line_pos + 1);    
    }
    while (text_line.size() > 0);
    return result;
}