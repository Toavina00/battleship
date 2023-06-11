#include "server.h"

int s_fd;
int sc_fd;

int createServer(int port)
{

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    if ((s_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Server creation");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(s_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Server bind");
        return -1;
    }

    printf("Server started: %s:%i\n", inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port));

    if (listen(s_fd, 1) < 0)
    {
        perror("Server listen");
        return -1;
    }

    int addrlen = sizeof(client_addr);
    if ((sc_fd = accept(s_fd, (struct sockaddr *)&client_addr, (socklen_t *)&addrlen)) < 0)
    {
        perror("Socket connection");
        return -1;
    }

    return 0;
}

void closeServer()
{
    shutdown(s_fd, SHUT_RDWR);
}