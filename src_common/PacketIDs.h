#ifndef PACKETIDS_H
#define PACKETIDS_H

enum PacketIDs {
    //Server to client
    ID_WAITING_CONNECT,         //tell the client we need to wait for another player to join
    ID_OTHER_PLAYED,            //indicate the client that the other client played
    ID_WAITING,                 //indicate the client it needs to wait for the other to play
    ID_REQUEST_PLAY,            //request the client to play
    ID_OTHER_LEFT,              //tell the client that the other player left


    //Client to server
    ID_PLAYED,                 //client telling the player which column it played
};

#endif