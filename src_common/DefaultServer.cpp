#include "DefaultServer.h"

#include <stdio.h>

DefaultServer::DefaultServer(enet_uint16 port) {
    m_address.host = ENET_HOST_ANY;
    m_address.port = port;        //server port

    m_server = enet_host_create(&m_address, 32, 1, 0, 0);
    if (m_server == NULL)
    {
        fprintf (stderr, "An error occurred while trying to create an ENet server host.\n");
        m_serverready = false;
        m_serverrunning = false;
        return;
    }

    m_serverready = true;
    m_serverrunning = true;
}

DefaultServer::~DefaultServer() {
    ENetEvent event;
    while(enet_host_service(m_server, &event, 3000) > 0) {      //Wait 3 second to be sure everyone is safely disconected
        switch(event.type) {
            case ENET_EVENT_TYPE_RECEIVE:
                enet_packet_destroy(event.packet);
                break;
        }
    }

    enet_host_destroy(m_server);
}


void DefaultServer::ServerRun() {
    while(m_serverrunning) {
        ServerDoTick();
    }
}

void DefaultServer::ServerDoTick() {
    if(!m_serverready) return;

    ENetEvent event;

    while(enet_host_service(m_server, &event, 10) > 0) {
        switch(event.type) {

            case ENET_EVENT_TYPE_CONNECT:
                printf("connection from %x\n", event.peer->address.host);
                ServerOnConnect(event);
                break;


            case ENET_EVENT_TYPE_DISCONNECT:
                printf("disconnection from %x\n", event.peer->address.host);
                ServerOnDisconnect(event);
                break;
            

            case ENET_EVENT_TYPE_RECEIVE:
                printf("Received packet from %x\n", event.peer->address.host);
                ServerOnReceive(event);
                enet_packet_destroy(event.packet);
                break;
        }
    }
}

void DefaultServer::ServerOnConnect(ENetEvent& event) {
    //To overwrite
    enet_uint32 ip   = event.peer->address.host;
    enet_uint32 port = event.peer->address.port;
    printf("Connection from %x:%i\n", ip, port);
}

void DefaultServer::ServerOnDisconnect(ENetEvent& event) {
    enet_uint32 ip   = event.peer->address.host;
    enet_uint32 port = event.peer->address.port;
    printf("Disconnected %x:%i\n", ip, port);
}

void DefaultServer::ServerOnReceive(ENetEvent& event) {
    enet_uint32 ip   = event.peer->address.host;
    enet_uint32 port = event.peer->address.port;

    unsigned char* pdata = event.packet->data;
    size_t datasize = event.packet->dataLength;

    printf("Received from %x:%i : ", ip, port);
    for(size_t i = 0; i < datasize; i++)
        printf("%x ", pdata[i]);
    printf("\n");
}