#pragma once

#include <string>
#include <map>
#include <memory>

struct Request {
    std::string verb;
    std::map<std::string, std::string> headers;
    std::unique_ptr<char[]> body;
    std::string path;

    static Request fromString(std::string str);
};

std::ostream& operator<<(std::ostream& io, const Request& r);