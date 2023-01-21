#ifndef DEFAULT_CLIENT_H
#define DEFAULT_CLIENT_H

#include <enet/enet.h>

class DefaultClient {
    public:
    DefaultClient(const char* hostName, enet_uint16 port);        //hostname = destination of the connection
    virtual ~DefaultClient();

    void DoTick();
    virtual void OnReceive(ENetEvent& event);
    virtual void OnDisconnect(ENetEvent& event);

    ENetHost* m_client;

    ENetAddress m_address;
    ENetPeer* m_peer;

    bool m_ready;
};

#endif