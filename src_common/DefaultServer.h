#ifndef DEFAULT_SERVER_H
#define DEFAULT_SERVER_H

#include <enet/enet.h>

class DefaultServer {
    public:
    DefaultServer(enet_uint16 port);
    virtual ~DefaultServer();

    virtual void Run();

    void DoTick();
    virtual void OnConnect(ENetEvent& event);
    virtual void OnDisconnect(ENetEvent& event);
    virtual void OnReceive(ENetEvent& event);

    ENetAddress m_address;
    ENetHost * m_server;

    bool m_ready;

    bool m_running;
};


#endif