#include "game.h"

int x, y;
char buff[BUFFER_SIZE];
char fb[BUFFER_SIZE];

int handleInput()
{

    if (buff[2] != '\0')
        return -1;
    else if (buff[0] == ':')
    {
        if (buff[1] == 'q' || buff[1] == 'Q')
        {
            return 1;
        }
        else if (buff[1] == 'w' || buff[1] == 'W')
        {
            return 2;
        }
    }
    else if ((buff[0] <= 'z' && buff[0] >= 'a') || (buff[0] <= 'Z' && buff[0] >= 'A'))
        if (buff[1] <= '9' && buff[1] >= '0')
        {
            y = buff[0];
            y -= (y <= 'J') ? 'A' : 'a';
            x = buff[1] - '0';
            return 0;
        }
    return -1;
}

int opponent(int c_fd)
{
    memset(buff, 0, BUFFER_SIZE);

    wlog("Waiting for the opponent");

    if (recv(c_fd, buff, BUFFER_SIZE, 0) < 0)
    {
        perror("Error on receiving data\n");
        return 1;
    }

    switch (handleInput())
    {
    case 1:
        wlog("The opponent ended the game");
        getch();
        return 0;
        break;

    case 2:
        wlog("Game Over: You won");
        getch();
        return 0;
        break;
    case 0:
        switch (attack(x, y))
        {
        case 0:
            strcpy(buff, " : Ship missed");
            send(c_fd, buff, strlen(buff), 0);
            break;
        case 1:
            strcpy(buff, " : Ship hit");
            send(c_fd, buff, strlen(buff), 0);
            break;
        case 2:
            strcpy(buff, " : Ship hit and sunk");
            send(c_fd, buff, strlen(buff), 0);
            break;
        default:
            break;
        }
        if (isOver())
        {
            strcpy(buff, ":w");
            wlog("Game Over: You Lost");
            send(c_fd, ":w", strlen(buff), 0);
            getch();
            return 0;
        }
        break;

    default:
        break;
    }

    return 1;
}

int player(int sc_fd)
{
    memset(buff, 0, BUFFER_SIZE);

Input:
    wlog("Enter \":Q\" or coordinate");
    getInput(buff);
    switch (handleInput())
    {
    case 1:
        wlog("You're ending the game");
        send(sc_fd, buff, strlen(buff), 0);
        getch();
        return 0;
        break;

    case 0:
        memset(fb, 0, BUFFER_SIZE);
        send(sc_fd, buff, strlen(buff), 0);
        strcpy(fb, buff);
        recv(sc_fd, buff, BUFFER_SIZE, 0);
        strcat(fb, buff);
        wfb(fb);
        break;

    default:
        goto Input;
        break;
    }

    return 1;
}

int startServer(int port)
{
    if (createServer(port) < 0)
    {
        return -1;
    }

    init();
    initwin();

    placeRandom(time(NULL));

    while (TRUE)
    {
        displayBoard();
        if (!player(sc_fd)) break;
        displayBoard();
        if (!opponent(sc_fd)) break;
    }

    return 0;
}

int startClient(int port, const char *addr)
{
    if (createClient(port, addr) < 0)
    {
        return -1;
    }

    init();
    initwin();

    placeRandom(time(NULL) + 1);

    while (TRUE)
    {
        displayBoard();
        if (!opponent(c_fd)) break;
        displayBoard();
        if (!player(c_fd)) break;
    }

    return 0;
}