#include "game.h"

int main(int argc, char const *argv[])
{
    if (argc == 1)
    {
        return -1;
    }
    else if (argc == 2)
    {
        return startServer(atoi(argv[1]));
    }
    else if (argc == 3)
    {
        if (strcmp(argv[1], "-s") == 0)
            return startServer(atoi(argv[2]));
        else
            return -1;
    }
    else if (argc == 4)
    {
        if (strcmp(argv[1], "-c") == 0)
            return startClient(atoi(argv[3]), argv[2]);
        else
            return -1;
    }
    else
        return -1;
}