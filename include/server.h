#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "window.h"

extern int s_fd;
extern int sc_fd;

int createServer(int port);
void closeServer();

#endif