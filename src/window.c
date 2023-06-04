#include "window.h"

int compRe() {

    if (!regcomp(&quit, "^:q$", REG_EXTENDED | REG_ICASE)) {
        perror("Regex compilation error");
        return -1;
    }
    if (!regcomp(&win, "^:w$", REG_EXTENDED | REG_ICASE)) {
        perror("Regex compilation error");
        return -1;
    }
    if (!regcomp(&target, "^[a-j][1-9]$", REG_EXTENDED | REG_ICASE)) {
        perror("Regex compilation error");
        return -1;
    }

    return 0;
}

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

    return compRe();

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

    if (!regexec(&quit, msg, 0, NULL, 0)) 
        return 1;
    else if (!regexec(&win, msg, 0, NULL, 0)) 
        return 2;
    else if (!regexec(&target, msg, 0, NULL, 0)) {
        if (x == NULL || y == NULL) return 0;
        *x = msg[0];
        *x -= (*x <= 'J')?'A':'a';
        *y = msg[1] - '0'; 
        return 0;
    }
    else return -1;
}


int getInput(char* buffer) {
    clearWin(iWin);
    mvwin(iWin, 1, 1);
    
    wgetstr(iWin, buffer);
    
    int out = handleInput(buffer, NULL, NULL);

    return (out == 2)?-1:out;
}