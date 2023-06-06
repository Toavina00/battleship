#include "client.h"

int createClient(int port, const char *addr)
{

    struct sockaddr_in s_addr;

    if ((c_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Client creation\n");
        return -1;
    }

    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = inet_addr(addr);
    s_addr.sin_port = htons(port);

    if (connect(c_fd, (struct sockaddr *)&s_addr, sizeof(s_addr)) < 0)
    {
        perror("Client connection\n");
        return -1;
    }

    return 0;
}

int startClient(int port, const char *addr)
{

    if (createClient(port, addr) != 0)
        return -1;

    init();
    placeRandom();
    initwin();

    while (true)
    {
        displayBoard(gWin);
        if (!oTurn())
            goto Over;
        displayBoard(gWin);
        if (!pTurn())
            goto Over;
    }

Over:

    delwin(gWin);
    delwin(dWin);
    delwin(iWin);
    endwin();

    return 0;
}