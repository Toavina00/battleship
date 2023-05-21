#ifndef CLIENT_H
#define CLIENT_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "piece.h"

int startClient(int port, const char* addr);

#endif