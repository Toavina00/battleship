#include "client.h"

int main() {
    init();
    placeRandom();

    startClient(5000, "127.0.0.1");

    return 0;
}