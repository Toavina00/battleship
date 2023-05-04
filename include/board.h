#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "time.h"

typedef struct b_case
{
    struct piece* piece;
    int state;
} b_case;

typedef struct board
{
    int width;
    int height;
    int n_shield;
    int n_defense;
    int n_radar;
    int n_offense;
    int n_admiral;
    b_case** board;
} board;

// Génère un terrain (w * h)
board createBoard(int, int);
// Place une piece dans le terrain
int placePiece(piece*, board*);

// Attaque dans un terrain donné
int attack(board*, int, int);
// Protège une piece dans un terrain donné
int shield(board*, int, int);
// Radar dans un terrain donné
int radar(board*, int, int);

// Liberation memoire
void delGame(board*);
#endif