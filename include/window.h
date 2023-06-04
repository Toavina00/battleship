#ifndef WINDOW_H
#define WINDOW_H

#include <string.h>
#include "piece.h"

static regex_t quit;
static regex_t win;
static regex_t target;

static WINDOW* gWin; 
static WINDOW* dWin;
static WINDOW* iWin;

int initwin();
int handleInput(char* msg, int* x, int* y);
int getInput(char* buffer);
void wlog(char* text);

#endif