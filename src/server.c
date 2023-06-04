#include "server.h"

int createServer(int port) {

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    if ((s_fd = socket(AF_INET, SOCK_STREAM, 0) ) < 0){
        perror("Server creation");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(s_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        perror("Server bind");
        return -1;
    }

    printf("Server started: %s:%i\n", inet_ntoa(server_addr.sin_addr) , server_addr.sin_port);

    if (listen(s_fd, 1) < 0) {
        perror("Server listen");
        return -1;
    }

    int addrlen = sizeof(client_addr);
    if ((c_fd = accept(s_fd, (struct sockaddr*) &client_addr, (socklen_t*) &addrlen)) < 0) {
        perror("Socket connection");
        return -1;
    }

    return 0;
}

int startServer(int port) {
    
    if (createServer(port) != 0) return -1;

    init();
    placeRandom();
    initwin();
    
    int x, y;
    while (true) {

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
                strcpy(buff, "Attack: Ship missed");
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

    }

    Over:

    delwin(gWin);
    delwin(dWin);
    delwin(iWin);
    endwin();

    shutdown(s_fd, SHUT_RDWR);

    return 0;

}
