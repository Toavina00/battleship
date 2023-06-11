#include "window.h"

WINDOW* gWin; 
WINDOW* dWin;
WINDOW* iWin;

int initwin() {

    initscr();
    cbreak();

    int maxX, maxY, posx, width = DIMENSION * 3 + 2, height = DIMENSION + 2;
    getmaxyx(stdscr, maxY, maxX);

    posx = (maxX - width)/2;
    gWin = newwin(height, width, 0, posx);
    dWin = newwin(3, width, height + 2, posx);
    iWin = newwin(3, width, height + 6, posx);

    box(iWin, 0, 0);

    box(dWin, 0, 0);
    mvwprintw(dWin, 0, 1, "Info");

    wrefresh(iWin);
    wrefresh(dWin);
    refresh();

}

void displayBoard() {

    for (int i = 0; i < DIMENSION; i++) {
        for (int j = 0; j < DIMENSION; j++) {
            int n = BOARD[i][j];
            printf("%i", n);
            mvwprintw(gWin, 1+i, 1+3*j, " %i ", n);
            if (BOARD[i][j] == 20) {
                mvwprintw(gWin, 1+i, 1+3*j, "   ");
            }
            else if (BOARD[i][j] == -20) {
                mvwprintw(gWin, 1+i, 1+3*j, " X ");
            }
            else if (BOARD[i][j] >= 1 && BOARD[i][j] <= N_PARTS) {
                wattron(gWin, A_REVERSE);
                mvwprintw(gWin, 1+i, 1+3*j, "   ");
                wattroff(gWin, A_REVERSE);
            }
            else {
                wattron(gWin, A_REVERSE);
                mvwprintw(gWin, 1+i, 1+3*j, " X ");
                wattroff(gWin, A_REVERSE);
            }
        }
    }

    box(gWin, 0, 0);
    for (int i = 0; i < DIMENSION; i++) {
        mvwprintw(gWin, 0, 1+3*i, " %c ", 'A' + i);
    }
    for (int i = 0; i < DIMENSION; i++) {
        mvwprintw(gWin, 1+i, 0, "%c", '0' + i );
    }

    wrefresh(gWin);
}

void freewin() {
    delwin(gWin);
    delwin(dWin);
    delwin(iWin);
    endwin();
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

void getInput(char* buffer) {
    clearWin(iWin);
    mvwgetstr(iWin, 1, 1, buffer);
}