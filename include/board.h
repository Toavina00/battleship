#ifndef BOARD_H
#define BOARD_H

#include "piece.h"

typedef struct b_case
{
    struct piece* piece;
    int state;
} b_case;

typedef struct board
{
    int width;
    int height;
    b_case* board;
};

#endif