#ifndef GAME_H
#define GAME_H

#include "server.h"
#include "client.h"

#define BUFFER_SIZE 512

extern int x, y;
extern char buff[BUFFER_SIZE];
extern char fb[BUFFER_SIZE];

int startServer(int port);
int startClient(int port, const char *addr);

#endif