#include <arpa/inet.h>
#include <memory>

class Server {
    private:
        static constexpr int BACKLOG = 10;
        int server_fd, client_fd;
        struct sockaddr_in server_addr{}, client_addr{};
        socklen_t sin_len = sizeof(client_addr);
        char buffer[2048];
    public:
        Server(int port);
        ~Server();

        Server(const Server& lhs) = delete;
        Server& operator=(const Server& lhs) = delete;

        void runForever(std::unique_ptr<char[]> (*func)(char*, long unsigned int));
};