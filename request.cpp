#include <sstream>
#include <string>
#include <cstring>
#include <iostream>

#include "request.h"

Request Request::fromString(std::string str) {
    std::map<std::string, std::string> headers{};
    std::stringstream ss{str};
    std::string verb{};
    
    std::getline(ss, verb);

    verb = verb.substr(0, verb.find("/")-1);

    for (std::string a; std::getline(ss, a) && a.size() > 1;) {
        const int colonAt = a.find(":");
        const std::string key = a.substr(0, colonAt);
        const std::string value = a.substr(colonAt + 2);
        headers[key] = value;
    }

    std::string body {
        std::istreambuf_iterator<char>(ss),
        std::istreambuf_iterator<char>(),
    };

    const size_t len = body.size();
    std::unique_ptr<char[]> bodyBuffer{new char[len]};
    std::memcpy(bodyBuffer.get(), body.data(), len);

    return Request{verb, headers, std::move(bodyBuffer)};
}

std::ostream& operator<<(std::ostream& io, const Request& r) {
    io << "Verb: " << r.verb << "\n";
    io << "Headers:\n";
    for (const auto& [key, value] : r.headers) {
        io << key << ": " << value << "\n";
    }
    io << "Body:\n" << r.body.get();
    return io;
}