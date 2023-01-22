#include "GameServer.h"

#include <stdio.h>

int main() {
    if(enet_initialize() != 0) {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
        return 1;
    }
    atexit(enet_deinitialize);

    GameServer myserver(1234);
    myserver.ServerRun();

    return 0;
}