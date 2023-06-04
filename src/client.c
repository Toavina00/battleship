#include "client.h"

int createClient(int port, const char* addr) {

    struct sockaddr_in s_addr;

    if ((c_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Client creation\n");
        return -1;
    }

    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = inet_addr(addr);
    s_addr.sin_port = htons(port);

    if (connect(c_fd, (struct sockaddr*) &s_addr, sizeof(s_addr)) < 0) {
        perror("Client connection\n");
        return -1;
    }

    return 0;
}

int startClient(int port, const char* addr) {

    if (createClient(port, addr) != 0) return -1;

    init();
    placeRandom();
    initwin();
    
    int x, y;
    while (true) {

        displayBoard(gWin);

        wlog("Waiting for the opponent");

        if (recv(c_fd, buff, 16, 0) < 0){
            perror("Error on receiving data\n");
            continue;
        }

        switch (handleInput(buff, &x, &y))
        {
        case 1:
            wlog("The opponent ended the game");
            getch();
            goto Over;
            break;
        
        case 2:
            wlog("Game Over: You won");
            getch();
            goto Over;
            break;
        case 0:
            switch(attack(y, x)) {
            case 0:
                strcpy(buff,"Attack: Ship missed");
                wlog(buff);
                send(c_fd, buff, strlen(buff), 0);
                break;   
            case 1:
                strcpy(buff,"Attack: Ship hit");
                wlog(buff);
                send(c_fd, buff, strlen(buff), 0);
                break;   
            case 2:
                strcpy(buff,"Attack: Ship hit and sunk");
                wlog(buff);
                send(c_fd, buff, strlen(buff), 0);
                break;
            default:
                break;   
            }
            if (isOver()) {
                wlog("Game Over: You Lost");
                send(c_fd, ":w", 3, 0);
                getch();
                goto Over;
            }
            break;

        default:
            break;
        }

        displayBoard(gWin);

        wlog("Enter \":Q\" or coordinate");

        Input:
        switch (getInput(buff))
        {
        case 1:
            wlog("You're ending the game");
            send(c_fd, buff, sizeof(buff), 0);
            getch();
            goto Over;
            break;
        
        case 0:
            send(c_fd, buff, sizeof(buff), 0);
            recv(c_fd, buff, sizeof(buff), 0);
            wlog(buff);
            break;

        default:
            wlog("Incorrect input");
            goto Input;
            break;
        }
    }

    Over:

    delwin(gWin);
    delwin(dWin);
    delwin(iWin);
    endwin();

    return 0;    
}