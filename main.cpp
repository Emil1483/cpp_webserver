#include <iostream>
#include <cstring>

#include "server.h"
#include "request.h"
#include "response.h"

int main() {
    Server server{8080};

    server.runForever([](char* buffer, int size) -> std::unique_ptr<char[]> {
        buffer[size] = '\0';
        std::cout << buffer << "\n";

        const std::string bufferString{buffer};
        const Request request = Request::fromString(bufferString);

        std::cout << request;

        const Response response {
            "200 OK", 
            {
                {"Content-Type", "text/html; charset=UTF-8"},
                {"Connection", "close"},
            }, 
            "<!DOCTYPE html>"
            "<html><head><title>Simple Server</title></head>"
            "<body><h1>Hello, world!</h1></body></html>"
        };
        
        auto payload = response.toString();
        const size_t len = payload.size();
        std::unique_ptr<char[]> responseBuffer{new char[len + 1]};
        std::memcpy(responseBuffer.get(), payload.data(), len + 1);

        return responseBuffer;
    });

    return 0;
}
