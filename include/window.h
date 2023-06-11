#ifndef WINDOW_H
#define WINDOW_H

#include "piece.h"

extern WINDOW *gWin;
extern WINDOW *dWin;
extern WINDOW *iWin;

int initwin();
void freewin();
void displayBoard();
void getInput(char *buffer);
void wlog(char *text);

#endif