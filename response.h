#pragma once

#include <string>
#include <map>

struct Response {
    std::string status;
    std::map<std::string, std::string> headers;
    std::string body;

    std::string toString() const;
};