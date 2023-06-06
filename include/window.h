#ifndef WINDOW_H
#define WINDOW_H

#include "piece.h"

static WINDOW* gWin; 
static WINDOW* dWin;
static WINDOW* iWin;

int initwin();
int handleInput(char* msg, int* x, int* y);
int getInput(char* buffer);
void wlog(char* text);

#endif