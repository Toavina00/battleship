#ifndef CLIENT_H
#define CLIENT_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "window.h"

static int c_fd;
static char buff[512];

int startClient(int port, const char* addr);

#endif