#include "piece.h"

piece createOffense(int pos_x, int pos_y, direction _dir) {
    piece p;
    p.x = pos_x;
    p.y = pos_y;
    p.type = OFFENSE;
    p.dir = _dir;
    p.shielded = 0;
    p.life = 4;
    return p;
}

piece createDefense(int pos_x, int pos_y, direction _dir) {
    piece p;
    p.x = pos_x;
    p.y = pos_y;
    p.type = DEFENSE;
    p.dir = _dir;
    p.shielded = 0;
    p.life = 4;
    return p;
}

piece createRadar(int pos_x, int pos_y, direction _dir) {
    piece p;
    p.x = pos_x;
    p.y = pos_y;
    p.type = RADAR;
    p.dir = _dir;
    p.shielded = 0;
    p.life = 3;
    return p;
}

piece createAdmiral(int pos_x, int pos_y, direction _dir) {
    piece p;
    p.x = pos_x;
    p.y = pos_y;
    p.type = ADMIRAL;
    p.dir = _dir;
    p.shielded = 0;
    p.life = 2;
    return p;
}