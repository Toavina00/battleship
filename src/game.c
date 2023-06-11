#include "game.h"

int x, y;
char buff[BUFFER_SIZE];

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

int opponent()
{

    int d_size = recv(c_fd, buff, BUFFER_SIZE, 0);
    if (recv(c_fd, buff, BUFFER_SIZE, 0) < 0)
    {
        perror("Error on receiving data\n");
        return 1;
    }
    buff[d_size] = '\0';

    switch (handleInput(buff, &x, &y))
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
            strcpy(buff, "Attack: Ship missed");
            wlog(buff);
            send(c_fd, buff, BUFFER_SIZE, 0);
            break;
        case 1:
            strcpy(buff, "Attack: Ship hit");
            wlog(buff);
            send(c_fd, buff, BUFFER_SIZE, 0);
            break;
        case 2:
            strcpy(buff, "Attack: Ship hit and sunk");
            wlog(buff);
            send(c_fd, buff, BUFFER_SIZE, 0);
            break;
        default:
            break;
        }
        if (isOver())
        {
            wlog("Game Over: You Lost");
            send(c_fd, ":w", BUFFER_SIZE, 0);
            getch();
            return 0;
        }
        break;

    default:
        break;
    }

    return 1;
}

int player()
{

    wlog("Enter \":Q\" or coordinate");

Input:
    getInput(buff);
    switch (handleInput(buff, &x, &y))
    {
    case 1:
        wlog("You're ending the game");
        send(sc_fd, buff, BUFFER_SIZE, 0);
        getch();
        return 0;
        break;

    case 0:
        send(sc_fd, buff, BUFFER_SIZE, 0);
        recv(sc_fd, buff, BUFFER_SIZE, 0);
        wlog(buff);
        mvwgetch(iWin, 1, 1);
        break;

    default:
        wlog("Incorrect input");
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

    placeRandom();

    while (TRUE)
    {
        /*TODO*/
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

    placeRandom();

    while (TRUE)
    {
        /*TODO*/
    }

    return 0;
}