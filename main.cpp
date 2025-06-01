#include <iostream>
#include <cstring>

#include "server.h"
#include "request.h"
#include "response.h"

Response handleRequest(const Request& req) {
    std::cout << req << "\n";
    return {
        StatusCodes::ok, 
        {
            {"Content-Type", "text/html; charset=UTF-8"},
            {"Connection", "close"},
        }, 
        "<!DOCTYPE html>"
        "<html><head><title>Simple Server</title></head>"
        "<body><h1>Hello, world!</h1></body></html>"
    };
}

std::unique_ptr<char[]> primitiveRequestHandler(char* buffer, long unsigned int size) {
    const std::string bufferString{buffer, size};

    Response response;
    try {
        const Request request = Request::fromString(bufferString);
        response = handleRequest(request);
    } catch (std::out_of_range e) {
        std::cerr << e.what() << "\n";

        response = Response{
            StatusCodes::payload_too_large, 
            {
                {"Content-Type", "text/html; charset=UTF-8"},
                {"Connection", "close"},
            },
            "The request was too big. It overflowed our buffer", 
        };
    }

    auto payload = response.toString();
    const size_t len = payload.size();
    std::unique_ptr<char[]> responseBuffer{new char[len + 1]};
    std::memcpy(responseBuffer.get(), payload.data(), len + 1);
    return responseBuffer;
}

int main() {
    Server server{8080};

    server.runForever(primitiveRequestHandler);

    return 0;
}
