#include "GameServer.h"

#include <PacketContent.h>
#include <PacketIDs.h> 

#include <stdio.h>


GameServer::GameServer(enet_uint16 port) : DefaultServer(port) {
    m_players[0] = NULL; m_players[1] = NULL;
    m_gamestarted = false;
    m_currentplayer = 0;
}

void GameServer::Run() {
    while(m_running) {
        DoTick();

        if(m_gamestarted == false) {
            if(m_players[1] != NULL && m_players[0] != NULL) {  //if two players are connected
                //Launch the game
                m_gamestarted = true;
                m_currentplayer = 0;

                //Tell player 1 it is his time to play
                PacketContent p;
                p.Append<char>(ID_REQUEST_PLAY);
                enet_peer_send(m_players[0], 0, p.MakePacket());

                //Tell player 2 to wait
                PacketContent p2;
                p2.Append<char>(ID_WAITING);
                enet_peer_send(m_players[1], 0, p2.MakePacket());
            }
        }
    }
}


void GameServer::OnConnect(ENetEvent& event) {
    if(m_gamestarted == false) {
        if(m_players[0] == NULL) {      //if it's the first player to join
            m_players[0] = event.peer;

            //Tell the client to wait
            PacketContent p;
            p.Append<char>(ID_WAITING_CONNECT);
            enet_peer_send(event.peer, 0, p.MakePacket());

            printf("As player 0\n");
        }
        else {                          //it it's the second player to join
            m_players[1] = event.peer;
            printf("As player 1\n");
        }
    }
}

void GameServer::OnDisconnect(ENetEvent& event) {
    printf("DISCONNECT\n");
    if(m_gamestarted) {     //if the game is started tell the other client the opponant disconnected
        m_gamestarted = false;  //stop the server

        int otherplayer = GetOtherPlayer(GetPlayerIndex(event.peer));   //get the index of the other player
        
        m_players[GetPlayerIndex(event.peer)] = NULL;   //remove the player from the list


        //tell the other client the opponant disconnected
        printf("Other player %i\n", otherplayer);
        PacketContent p;
        p.Append<char>(ID_OTHER_LEFT);
        enet_peer_send(m_players[otherplayer], 0, p.MakePacket());
    }
    else {                  //else just remove the player
        int player = GetPlayerIndex(event.peer);
        m_players[player] = NULL;
    }
}

void GameServer::OnReceive(ENetEvent& event) {
    unsigned char* pdata = event.packet->data;
    unsigned char packetid = pdata[0];

    printf("Got ID %i\n", packetid);
    
    switch(packetid) {
        case ID_PLAYED:
            {
                //printf("ID_PLAYED\n");

                unsigned char column = pdata[1];
                int player = GetPlayerIndex(event.peer);

                if(player == m_currentplayer) {
                    PacketContent p;
                    p.Append<char>(ID_WAITING);
                    enet_peer_send(event.peer, 0, p.MakePacket());

                    PacketContent p2;
                    p2.Append<char>(ID_OTHER_PLAYED);
                    p2.Append<char>(column);
                    enet_peer_send(m_players[GetOtherPlayer(player)], 0, p2.MakePacket());

                    m_currentplayer = GetOtherPlayer(player);

                    printf("Next turn\n");
                }
            }
        break;

        default:
            printf("Unknown packet received\n");
        break;
    }


}



int GameServer::GetPlayerIndex(ENetPeer* peer) {
    if(m_players[0] == peer) return 0;
    if(m_players[1] == peer) return 1;
    return -1;
}

int GameServer::GetOtherPlayer(int index) {
    if(index == 1) return 0;
    return 1;
}