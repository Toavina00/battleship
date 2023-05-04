#ifndef PIECE_H
#define PIECE_H

#include <stdio.h>

typedef enum Class
{
    OFFENSE,
    DEFENSE,
    ADMIRAL,
    RADAR,
} Class;

typedef enum direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
} direction;

typedef struct piece
{
    int x;
    int y;
    int life;
    int shielded;
    Class type;
    direction dir;
} piece;

#endif