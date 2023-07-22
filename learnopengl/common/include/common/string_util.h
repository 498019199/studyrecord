#include <string>
#include <string_view>
#include <vector>
#include <regex>

namespace CommonWorker
{
std::vector<std::string_view> stringSplit(const std::string& str, char delim) 
{
    std::string s;
    s.append(1, delim);
    std::regex reg(s);
    std::vector<std::string_view> elems(std::sregex_token_iterator(str.begin(), str.end(), reg, -1),
                                   std::sregex_token_iterator());
    return elems;
}
}