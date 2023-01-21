#include "DefaultClient.h"

#include <stdio.h>

DefaultClient::DefaultClient(const char* hostName, enet_uint16 port) {
    m_client = enet_host_create(NULL, 1, 1, 0, 0);
    if(m_client == NULL) {
        fprintf (stderr, "An error occurred while creating an ENet client.\n");
        m_ready = false;
        return;
    }

    enet_address_set_host(&m_address, hostName);
    m_address.port = port;

    m_peer = enet_host_connect(m_client, &m_address, 1, 0);
    if(m_peer == NULL) {
        fprintf (stderr, "Failed to connect to the peer.\n");
        m_ready = false;
        return;
    }

    ENetEvent event;
    if(enet_host_service(m_client, &event, 100) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
        printf("success\n");
    }
    else {
        enet_peer_reset(m_peer);
        printf("connection failed\n");
        m_ready = false;
        return;
    }

    m_ready = true;
}

//This will correctly disconnect the client host (m_client) from the server (m_peer)
DefaultClient::~DefaultClient() {
    if(!m_ready) return;
    
    printf("disconnecting...\n"),
    enet_peer_disconnect(m_peer, 0);
    bool disconnectsuccess = false;

    ENetEvent event;
    while (enet_host_service(m_client, &event, 3000) > 0) {     //wait for the server to confirm the deconnection
        switch (event.type)
        {
        case ENET_EVENT_TYPE_RECEIVE:
            enet_packet_destroy(event.packet);
            break;

        case ENET_EVENT_TYPE_DISCONNECT:
            puts ("Disconnection succeeded.");
            disconnectsuccess = true;
            enet_host_destroy(m_client);
            return;     //the disconnection have been confirmed, there is no need to wait longer.
        }
    }

    if(disconnectsuccess == false) {
        printf("Forcing disconnection\n");
        enet_peer_reset(m_peer);
    }
    enet_host_destroy(m_client);
}

///////////////////////////////
//Handle packets

void DefaultClient::DoTick() {
    if(!m_ready) return;

    ENetEvent event;
    while(enet_host_service(m_client, &event, 10) > 0) {
        //printf("EVENT\n");
        switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE:
                OnReceive(event);
                enet_packet_destroy(event.packet);
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                OnDisconnect(event);

            default:
                break;
        }
    }
}

void DefaultClient::OnReceive(ENetEvent& event) {
    unsigned char* pdata = event.packet->data;
    size_t datasize = event.packet->dataLength;
    
    printf("Received : ");
    for(size_t i = 0; i < datasize; i++)
        printf("%x ", pdata[i]);
    printf("\n");
}

void DefaultClient::OnDisconnect(ENetEvent& event) {
    //To override
}