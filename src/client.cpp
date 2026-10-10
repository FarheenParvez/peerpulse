#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    //1. create a tcp socket
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_fd == -1) {
        std::cerr << "socket failed: " << strerror(errno) << '\n';
        return 1;
    }

    //2. Configure the server
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);

    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) != 1) {
        std::cerr << "Invalid server address\n";
        close(sock_fd);
        return 1;
    }

    //3. connect to server
    if(connect(sock_fd, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) == -1) {
        std::cerr << "connect failed: " << strerror(errno) << '\n';
        close(sock_fd);
        return 1;
    }

    std::cout << "Connected to PeerPulse server!\n";

        // 4. Send a message.
    const char message[] = "Hello from PeerPulse client!";

    ssize_t bytes_sent = send(
        sock_fd, message, sizeof(message) - 1, 0
    );

    if (bytes_sent == -1) {
        std::cerr << "send failed: " << strerror(errno) << '\n';
        close(sock_fd);
        return 1;
    }

    std::cout << "Sent " << bytes_sent << " bytes.\n";

    // 5. Close the connection.
    close(sock_fd);

    return 0;


}