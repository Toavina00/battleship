#include "window.h"

int initwin() {

    initscr();
    cbreak();

    int maxX, maxY, posx, width = DIMENSION * 3 + 2, height = DIMENSION + 2;
    getmaxyx(stdscr, maxY, maxX);

    posx = (maxX - width)/2;
    gWin = newwin(height, width, 0, posx);
    dWin = newwin(3, width, height + 3, posx);
    iWin = newwin(3, width, height + 9, posx);

    box(iWin, 0, 0);

    box(dWin, 0, 0);
    mvwprintw(dWin, 0, 1, "Info");

    box(gWin, 0, 0);
    for (int i = 0; i < DIMENSION; i++) {
        mvwprintw(gWin, 0, 1+3*i, " %c ", 'A' + i);
    }
    for (int i = 0; i < DIMENSION; i++) {
        mvwprintw(gWin, 1+i, 0, "%c", '0' + i );
    }

    wrefresh(iWin);
    wrefresh(gWin);
    wrefresh(dWin);
    refresh();

}

void clearWin(WINDOW* win) {
    wclear(win);
    box(win, 0, 0);
}

void wlog(char* text) {
    clearWin(dWin);
    mvwprintw(dWin, 0, 1, "Info");
    mvwprintw(dWin, 1, 1, text);
    wrefresh(dWin);
}


int handleInput(char* msg, int* x, int* y) {    

    if (msg[2] == '\0') 
        return -1;
    else if (msg[0] == ':') {
        if (msg[1] == 'q' || msg[1] == 'Q') {
            return 1;
        } else if (msg[1] == 'w' || msg[1] == 'W') {
            return 2;
        }
    }
    else if ( (msg[0] <= 'z' && msg[0] >= 'a') || (msg[0] <= 'Z' && msg[0] >= 'A') ) 
        if (msg[1] <= '9' && msg[1] >= '0') {
            if (x == NULL || y == NULL) return 0;
            *x = msg[0];
            *x -= (*x <= 'J')?'A':'a';
            *y = msg[1] - '0'; 
            return 0;
        }
    return -1;
}


int getInput(char* buffer) {
    clearWin(iWin);
    mvwgetstr(iWin, 1, 1, buffer);
    
    int out = handleInput(buffer, NULL, NULL);

    return (out == 2)?-1:out;
}