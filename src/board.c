#include "board.h"

board createBoard(int w, int h) {
    board b;
    b.width = w;
    b.height = h;
    b.board = (b_case**) malloc(h * sizeof(b_case*));
    for (int i = 0; i < h; i++) {
        b.board[i] = (b_case*) malloc(w * sizeof(b_case));
        for (int j = 0; j < w; j++) {
            b.board[i][j].piece = NULL;
            b.board[i][j].state = 0;
        }
    }
    return b;
}

int placePiece(piece* p, board* b) {
    if (p->x < 0 || p->x >= b->width || p->y < 0 || p->y >= b->height) return 0;
    switch (p->dir)
    {
    case UP:
        if (p->y - (p->life - 1) < 0 || b->board[p->y][p->x].piece != NULL) return 0;
        for (int i = 0; i < p->life; i++) {
            b->board[p->y - i][p->x].piece = p;
        }
        break;
    
    case DOWN:
        if (p->y + (p->life - 1) >= b->height || b->board[p->y][p->x].piece != NULL) return 0;
        for (int i = 0; i < p->life; i++) {
            b->board[p->y + i][p->x].piece = p;
        }
        break;

    case LEFT:
        if (p->x - (p->life - 1) < 0 || b->board[p->y][p->x].piece != NULL) return 0;
        for (int i = 0; i < p->life; i++) {
            b->board[p->y][p->x - i].piece = p;
        }
        break;

    case RIGHT:
        if (p->x + (p->life - 1) >= b->width || b->board[p->y][p->x].piece != NULL) return 0;
        for (int i = 0; i < p->life; i++) {
            b->board[p->y][p->x + i].piece = p;
        }
        break;
    }
    return 1;
}

void delGame(board* b) {
    for (int i = 0; i < b->height; i++)
    {
        for (int j = 0; j < b->width; j++)
        {
            free(b->board[i][j].piece);
        }
        free(b->board[i]);
    }
    free(b->board);
}

void replace(board* b, piece* p) {
    int success = 0, x, y, d;
    while (!success) {
        switch (p->dir)
        {
        case UP: 
            for (int i = 0; i < p->life; i++) {
                b->board[p->y - i][p->x].piece = NULL;
            }
            break;

        case DOWN:
            for (int i = 0; i < p->life; i++) {
                b->board[p->y + i][p->x].piece = NULL;
            }
            break;

        case LEFT:
            for (int i = 0; i < p->life; i++) {
                b->board[p->y][p->x - i].piece = NULL;
            }
            break;

        case RIGHT:
            for (int i = 0; i < p->life; i++) {
                b->board[p->y][p->x + i].piece = NULL;
            }
            break;
        }
        x = rand() % b->width;
        y = rand() % b->height;
        d = rand() % 4;
        p->x = x; p->y = y; p->dir = d;
        success = placePiece(p, b);
    }
}

int attack(board* b, int x, int y) {
    if (x < 0 || x >= b->width || y < 0 || y >= b->height) return 0;
    if (b->board[y][x].state == 1) return 0;
    if (b->board[y][x].piece != NULL) {
        if (b->board[y][x].piece->shielded) {
            b->board[y][x].piece->shielded = 0;
            b->n_shield--;
            return 0;
        }
        switch (b->board[y][x].piece->type) {
            case ADMIRAL:
                b->board[y][x].piece->life--;
                if (b->board[y][x].piece->life = 0) {
                    b->n_admiral--;
                } else {
                    replace(b, b->board[y][x].piece);
                }
                break;

            case OFFENSE:
                b->board[y][x].piece->life--;
                b->board[y][x].state = 1;
                if (b->board[y][x].piece->life = 0) {
                    b->n_offense--;
                }
                break;

            case DEFENSE:
                b->board[y][x].piece->life--;
                b->board[y][x].state = 1;
                if (b->board[y][x].piece->life = 0) {
                    b->n_defense--;
                }
                break;

            case RADAR:
                b->board[y][x].piece->life--;
                b->board[y][x].state = 1;
                if (b->board[y][x].piece->life = 0) {
                    b->n_radar--;
                }
                break;
        }
        return 1;
    }
    return 0;
}

int shield(board* b, int x, int y) {
    if (x < 0 || x >= b->width || y < 0 || y >= b->height) return 0;
    if (b->n_shield == 2) return 0;
    if (b->n_defense == 0) return 0;
    if (b->board[y][x].piece != NULL) {
        if (b->board[y][x].piece->shielded) {
            return 0;
        }
        switch (b->board[y][x].piece->type) {
            case OFFENSE:
                b->board[y][x].piece->shielded = 1;
                b->n_shield++;
                break;

            case RADAR:
                b->board[y][x].piece->shielded = 1;
                b->n_shield++;
                break;

            default:
                return 0;
                break;
        }
        return 1;
    }
    return 0;
}

int radar(board* b, int x, int y) {
    if (x < 0 || x >= b->width || y < 0 || y >= b->height) return 0;
    if (b->n_radar == 0) return 0;
    for (int i = 0; i < 2; i++) {
        if (!(x < 0 || x >= b->width || y - i < 0 || y - i >= b->height)) 
            if (b->board[y - i][x].piece != NULL) return 1;
        if (!(x - i < 0 || x - i >= b->width || y < 0 || y >= b->height)) 
            if (b->board[y][x - i].piece != NULL) return 1;
        if (!(x < 0 || x >= b->width || y + i < 0 || y + i >= b->height)) 
            if (b->board[y + i][x].piece != NULL) return 1;
        if (!(x + i < 0 || x + i >= b->width || y < 0 || y >= b->height)) 
            if (b->board[y][x + i].piece != NULL) return 1;
    }
    return 0;
}