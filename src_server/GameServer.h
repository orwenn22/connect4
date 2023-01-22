#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include <DefaultServer.h>

//TODO : make the server keep track of the grid and check if a player won.

class GameServer : public DefaultServer {
    public:
    GameServer(enet_uint16 port);

    void ServerRun() override;
    void ServerOnConnect(ENetEvent& event) override;
    void ServerOnDisconnect(ENetEvent& event) override;
    void ServerOnReceive(ENetEvent& event) override;

    int GetPlayerIndex(ENetPeer* peer);
    int GetOtherPlayer(int index);

    ENetPeer* m_players[2];
    bool m_gamestarted;
    int m_currentplayer;
};

#endif