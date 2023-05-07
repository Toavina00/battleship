#include "server.h"

int serverStart(int port) {

    int s_fd, c_fd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    if ((s_fd = socket(AF_INET, SOCK_STREAM, 0) ) < 0){
        perror("Server creation");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(s_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        perror("Server bind");
        return -1;
    }

    if (listen(s_fd, 1) < 0) {
        perror("Server listen");
        return -1;
    }

    int addrlen = sizeof(client_addr);
    if ((c_fd = accept(s_fd, (struct sockaddr*) &client_addr, (socklen_t*) &addrlen)) < 0) {
        perror("Socket connection");
        return -1;
    }

    int running = 1;
    while (running) {
        // TODO
    }

    shutdown(s_fd, SHUT_RDWR);

    return 0;
}