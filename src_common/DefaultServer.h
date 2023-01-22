#ifndef DEFAULT_SERVER_H
#define DEFAULT_SERVER_H

#include <enet/enet.h>

class DefaultServer {
    public:
    DefaultServer(enet_uint16 port);
    virtual ~DefaultServer();

    virtual void ServerRun();

    void ServerDoTick();
    virtual void ServerOnConnect(ENetEvent& event);
    virtual void ServerOnDisconnect(ENetEvent& event);
    virtual void ServerOnReceive(ENetEvent& event);

    ENetAddress m_address;
    ENetHost * m_server;

    bool m_ready;

    bool m_running;
};


#endif