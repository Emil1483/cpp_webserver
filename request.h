#include <string>
#include <map>

struct Request {
    std::string verb;
    std::map<std::string, std::string> headers;
    char* body;
};