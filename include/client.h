#ifndef CLIENT_H
#define CLIENT_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "window.h"

extern int c_fd;

int createClient(int port, const char *addr);

#endif