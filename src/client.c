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

    char buff[16];
    char input[16];

    init();
    placeRandom();

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

    regex_t quit;
    regex_t target;

    if (!regcomp(&quit, "^quit$", 0)) {
        perror("Regex compilation error");
        return 1;
    }
    if (!regcomp(&target, "^[:number:] [:number:]$", 0)) {
        perror("Regex compilation error");
        return 1;
    }
    
    while (true) {
        displayBoard(gWin);

        if (recv(c_fd, buff, 16, 0) < 0){
            perror("Error on receiving data");
        }

        if (!regexec(&quit, buff, 0, NULL, REG_ICASE)) {
            wclear(dWin);
            mvwprintw(dWin, 1, 1, "The opponent quitted");
            getch();
            goto Over;
        }

        char* msg;
        switch(attack(buff[0] - '0', buff[2] - '0')) {
        case 0:
            msg = "Miss";
            send(c_fd, msg, strlen(msg), 0);
            break;   
        case 1:
            msg = "Hit";
            send(c_fd, msg, strlen(msg), 0);
            break;   
        case 2:
            msg = "Hit and sunk";
            send(c_fd, msg, strlen(msg), 0);
            break;
        default:
            break;   
        }

        if (isOver()) {
            mvwprintw(dWin, 1, 1, "Game Over: You lost");
            getch();
            goto Over;
        }

        wclear(dWin);
        mvwprintw(dWin, 1, 1, "Enter \"quit\" to quit the game or \"{row} {column}\" to attack");
        while (true) {
            wclear(iWin);
            mvwin(iWin, 1, 1);
            getstr(input);
            if (!regexec(&quit, input, 0, NULL, REG_ICASE)) {
                wclear(dWin);
                mvwprintw(dWin, 1, 1, "You are quitting the game");
                getch();
                goto Over;  
            }
            if (!regexec(&target, input, 0, NULL, 0)) {
                wclear(dWin);
                mvwprintw(dWin, 1, 1, "Wrong input please try again");
                continue;
            } else {
                break;
            }
        }

        wclear(dWin);
        
        wrefresh(gWin);
        wrefresh(dWin);
        wrefresh(iWin);
    }

    Over:

    delwin(gWin);
    delwin(dWin);
    delwin(iWin);
    endwin();

    return 0;    
}