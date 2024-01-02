#include <filesystem>
#include <fstream>
#include <sstream>

namespace CommonWorker
{
std::string GetFileContents(const char* filename)
{   
    std::ifstream fp(filename);
    if (!fp.is_open()) 
    {
        return "";
    }
    std::ostringstream oss;
    oss << fp.rdbuf();
    std::string content = oss.str();
    fp.close();

    return content;
}
}