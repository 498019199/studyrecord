#pragma once
#include <string>

namespace common_work
{
std::vector<std::string> split(const std::string& src, std::string delimiter = ",") 
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = src.find(delimiter, pos_start)) != std::string::npos) {
        token = src.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }
    res.push_back (src.substr (pos_start));
    return res;
}
} // namespace common_work
