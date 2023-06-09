#ifndef GAME_H
#define GAME_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "window.h"

static int c_fd, x, y;
static char buff[512];

int pTurn();
int oTurn();

#endif