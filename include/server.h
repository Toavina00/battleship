#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "window.h"

static int s_fd;
static int c_fd;
static char buff[512];

int startServer(int port);

#endif