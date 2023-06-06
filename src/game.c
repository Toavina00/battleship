#include "game.h"

int oTurn()
{
    wlog("Waiting for the opponent");

    if (recv(c_fd, buff, 16, 0) < 0)
    {
        perror("Error on receiving data\n");
        return 1;
    }

    switch (handleInput(buff, &x, &y))
    {
    case 1:
        wlog("The opponent ended the game");
        getch();
        return;
        break;

    case 2:
        wlog("Game Over: You won");
        getch();
        return 0;
        break;
    case 0:
        switch (attack(y, x))
        {
        case 0:
            strcpy(buff, "Attack: Ship missed");
            wlog(buff);
            send(c_fd, buff, strlen(buff), 0);
            break;
        case 1:
            strcpy(buff, "Attack: Ship hit");
            wlog(buff);
            send(c_fd, buff, strlen(buff), 0);
            break;
        case 2:
            strcpy(buff, "Attack: Ship hit and sunk");
            wlog(buff);
            send(c_fd, buff, strlen(buff), 0);
            break;
        default:
            break;
        }
        if (isOver())
        {
            wlog("Game Over: You Lost");
            send(c_fd, ":w", 3, 0);
            getch();
            return 0;
        }
        break;

    default:
        break;
    }

    return 1;
}

int pTurn()
{

    wlog("Enter \":Q\" or coordinate");

Input:
    switch (getInput(buff))
    {
    case 1:
        wlog("You're ending the game");
        send(c_fd, buff, sizeof(buff), 0);
        getch();
        return 0;
        break;

    case 0:
        send(c_fd, buff, sizeof(buff), 0);
        recv(c_fd, buff, sizeof(buff), 0);
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