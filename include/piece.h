#ifndef PIECE_H
#define PIECE_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#define N_SHIPS 5
#define N_PARTS 17
#define DIMENSION 10

/*-------------------*/
//  Data Structures  //
/*-------------------*/

typedef enum Orientation
{
    UP,
    DOWN,
    RIGHT,
    LEFT
} Orientation;

typedef struct Ship
{
    int id;
    int length;
    int offset;
} Ship;

typedef struct Part
{
    int id;
    int ownerId;
} Part;

/*-------------------*/
//    Game Pieces    //
/*-------------------*/

extern Ship SHIPS[N_SHIPS];
extern Part PARTS[N_PARTS];

extern int BOARD[DIMENSION][DIMENSION];

/*-------------------*/
//   Game Functions  //
/*-------------------*/

void init();
void debug();
int isOver();
int place(int, int, int, Orientation);
void placeRandom(unsigned int);
int attack(int, int);

#endif