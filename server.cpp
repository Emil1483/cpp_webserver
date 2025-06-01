#include "server.h"
#include <stdexcept>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

Server::~Server() {
    close(server_fd);
}

Server::Server(int port) {
    // 1) Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        throw std::runtime_error("socket");
    }

    // 2) Allow quick reuse of the port
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        close(server_fd);
        throw std::runtime_error("setsockopt");
    }

    // 3) Bind to all interfaces on PORT
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        close(server_fd);
        throw std::runtime_error("bind");
    }

    // 4) Listen for incoming connections
    if (listen(server_fd, BACKLOG) < 0) {
        close(server_fd);
        throw std::runtime_error("listen");
    }

    std::cout << "Listening on port " << port << "...\n";
}

void Server::runForever(std::unique_ptr<char[]> (*func)(char*, int)) {
    while (true) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &sin_len);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        std::cout << "Connection from "
            << inet_ntoa(client_addr.sin_addr)
            << ":" << ntohs(client_addr.sin_port) << "\n";
        
        ssize_t read_len = read(client_fd, buffer, sizeof(buffer) - 1);
        std::unique_ptr<char[]> response = func(buffer, read_len);

        write(client_fd, response.get(), strlen(response.get()));
        close(client_fd);
    }
}