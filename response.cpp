#include "response.h"

std::string Response::toString() const {
    std::string result{};

    result += "HTTP/1.1 " + status + "\r\n";
    for (const auto&[key, value] : headers) {
        result += key + ": " + value + "\r\n";
    }
    result += "\r\n";
    result += body;
    return result;
}