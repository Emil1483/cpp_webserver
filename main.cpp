#include <iostream>
#include <cstring>
#include "server.h"

int main() {
    Server server{8080};

    server.runForever([](char* buffer, int size) -> std::unique_ptr<char[]> {
        buffer[size] = '\0';
        std::cout << buffer << "\n";

        std::string payload =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n"
            "Connection: close\r\n"
            "\r\n"
            "<!DOCTYPE html>"
            "<html><head><title>Simple Server</title></head>"
            "<body><h1>Hello, world!</h1></body></html>";
        
        const size_t len = payload.size();
        std::unique_ptr<char[]> responseBuffer{new char[len + 1]};
        std::memcpy(responseBuffer.get(), payload.data(), len + 1);

        return responseBuffer;
    });

    return 0;
}
