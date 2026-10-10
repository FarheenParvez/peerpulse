#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

int main() {

    //1. creaate a tcp socket
    int server_fd  = socket(AF_INET, SOCK_STREAM, 0);

    if(server_fd == -1) {
        std::cerr << "socket failed: " << strerror(errno) << '\n';
        return 1;
    }

    //2. COnfigure the server address
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    //3. Bind the socket to 127.0.0.1:8080
    if(bind(server_fd, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) == -1) {
        std::cerr << "bind failed: " << strerror(errno) << '\n';

        close(server_fd);
        return 1;
    }

    //4. Mark the socket as listening socket
    if(listen(server_fd, 5) == -1) {
        std::cerr << "listen failed: " << strerror(errno) << '\n'; 
        close(server_fd);
        return 1;  
    }

    std::cout << "PeerPulse server listening on port 8080...\n";
    
    //5. Wait for client connection
    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);

    int client_fd = accept(server_fd, reinterpret_cast<sockaddr*>(&client_addr), &client_len);

        if (client_fd == -1) {
        std::cerr << "accept failed: "
                  << strerror(errno) << '\n';
        close(server_fd);
        return 1;
    }

    std::cout << "Client connected!\n";

    //6. Receive data from client
    char buffer[1024];

    ssize_t bytes_recevied = recv(client_fd, buffer, sizeof(buffer) -1, 0);

    if(bytes_recevied > 0) {
        buffer[bytes_recevied] = '\0';
        std::cout << "Received: " << buffer << '\n';
    } else if (bytes_recevied == 0) {
        std::cout << "Client disconnected.\n";
    } else {
        std::cerr << "recv failed: " << strerror(errno) << '\n';
    }

    //7. close both descritors
    close(client_fd);
    close(server_fd);

    return 0;

}