#include "client.h"

int startClient(int port, const char* addr) {

    int c_fd;
    struct sockaddr_in s_addr;

    if ((c_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Client creation");
        return -1;
    }

    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = inet_addr(addr);
    s_addr.sin_port = htons(port);

    if (connect(c_fd, (struct sockaddr*) &s_addr, sizeof(s_addr)) < 0) {
        perror("Client connection");
        return -1;
    }

    int running = 1;
    while (running) {
        // TODO
    }
    
}