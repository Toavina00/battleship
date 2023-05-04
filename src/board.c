#include "board.h"

board createBoard(int w, int h) {
    board b;
    b.width = w;
    b.height = h;
    b.board = (b_case**) malloc(h * sizeof(b_case*));
    for (int i = 0; i < h; i++) {
        b.board[i] = (b_case*) malloc(w * sizeof(b_case));
    }
    return b;
}