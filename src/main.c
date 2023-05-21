#include "client.h"

int main() {
    initscr();
    WINDOW* win = newwin(10, 10, 5, 5);
    box(win, 0, 0);
    wrefresh(win);
    refresh();
    getch();
    mvwprintw(win, 1, 1, "Test");
    getch();
    wclear(win);
    getch();
    delwin(win);
    endwin();

    return 0;
}