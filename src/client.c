#include "client.h"

int startClient(int port, const char* addr) {

    int c_fd;
    struct sockaddr_in s_addr;

    if ((c_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Client creation");
        return -1;
    }

    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = inet_addr(addr);
    s_addr.sin_port = htons(port);

    if (connect(c_fd, (struct sockaddr*) &s_addr, sizeof(s_addr)) < 0) {
        perror("Client connection");
        return -1;
    }

    char buff[512];

    initscr();
    cbreak();

    int maxX, maxY, posx, width = DIMENSION * 3 + 2, height = DIMENSION + 2;
    getmaxyx(stdscr, maxY, maxX);

    posx = (maxX - width)/2;
    WINDOW* gWin = newwin(height, width, 0, posx);
    WINDOW* dWin = newwin(3, width, height + 3, posx);
    WINDOW* iWin = newwin(3, width, height + 9, posx);

    box(dWin, 0, 0);
    mvwprintw(dWin, 0, 1, "Info");

    box(iWin, 0, 0);
    mvwprintw(iWin, 0, 1, "Player");

    box(gWin, 0, 0);
    for (int i = 0; i < DIMENSION; i++) {
        mvwprintw(gWin, 0, 1+3*i, " %c ", 'A' + i);
    }
    for (int i = 0; i < DIMENSION; i++) {
        mvwprintw(gWin, 1+i, 0, "%c", '0' + i );
    }

    while (true) {
        displayBoard(gWin);

        
        
        wrefresh(gWin);
        wrefresh(dWin);
        wrefresh(iWin);
    }

    delwin(gWin);
    delwin(dWin);
    delwin(iWin);
    endwin();

    return 0;    
}