#include <sstream>
#include <string>
#include <cstring>
#include <iostream>

#include "request.h"

Request Request::fromString(std::string str) {
    std::map<std::string, std::string> headers{};
    std::stringstream ss{str};
    
    std::string firstLine{};
    std::getline(ss, firstLine);

    const auto i =  firstLine.find(" ");
    const auto j =  firstLine.find(" ", i + 1);

    const auto verb = firstLine.substr(0, i);
    const auto path = firstLine.substr(i + 1, j - i);

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

    const auto len = std::stoi(headers.at("Content-Length"));

    if (len > body.size()) {
        throw std::out_of_range("Request overflowed the buffer");
    }

    std::unique_ptr<char[]> bodyBuffer{new char[len + 1]};
    std::memcpy(bodyBuffer.get(), body.data(), len);
    bodyBuffer[len] = '\0';

    return Request{verb, headers, std::move(bodyBuffer), path};
}

std::ostream& operator<<(std::ostream& io, const Request& r) {
    io << "Path: " << r.path << "\n";
    io << "Verb: " << r.verb << "\n";
    io << "Headers:\n";
    for (const auto& [key, value] : r.headers) {
        io << key << ": " << value << "\n";
    }
    io << "Body:\n" << r.body.get();
    return io;
}