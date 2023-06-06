#ifndef PIECE_H
#define PIECE_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#define N_SHIPS    5
#define N_PARTS    17
#define DIMENSION  10

/*-------------------*/
//  Data Structures  //
/*-------------------*/

typedef enum Orientation {
    UP, DOWN, RIGHT, LEFT
} Orientation;

typedef struct Ship {
    int id;
    int length;
    int offset;
}Ship;

typedef struct Part {
    int id;
    int ownerId;
} Part;

/*-------------------*/
//    Game Pieces    //
/*-------------------*/

static Ship SHIPS[N_SHIPS];
static Part PARTS[N_PARTS];

static int BOARD[DIMENSION][DIMENSION];

/*-------------------*/
//   Game Functions  //
/*-------------------*/

void init();
int isOver();
int place(int, int, int, Orientation);
void placeRandom();
void displayBoard(WINDOW*);
int attack(int, int);

#endif