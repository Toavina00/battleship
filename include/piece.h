#ifndef PIECE_H
#define PIECE_H

#include <stdio.h>

typedef enum Class
{
    OFFENSE,
    DEFENSE,
    ADMIRAL,
    SHIELD,
} Class;

typedef struct piece
{
    int x;
    int y;
    int direction;
    int life;
    int shielded;
    Class type;
} piece;

#endif