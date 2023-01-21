#include "GameState.h"

#include "MenuState.h"

#include <Engine/Engine.h>

#include <PacketContent.h>
#include <PacketIDs.h>

#include <raylib.h>
#include <stdio.h>

const Color cols[] = {
    {0, 0, 0, 255},
    {255, 0, 0, 255},
    {255, 255, 0, 255}
};

GameState::GameState(char* hostName, unsigned short port) : State() , DefaultClient(hostName, port) {
    for(int i = 0; i < 6*7; i++)
        m_grid[i] = 0;
    

    m_gamestate = GS_WAITING_PLAYER_CONNECTION;

}

void GameState::OnParrentAdd() {
    if(m_ready == false) {  //check if the connection was successful
        printf("NO >:(\n");
        m_manager->SetState(new MenuState("Connection failed"));
        return;
    }
}

void GameState::Update() {
    DoTick();   //client connection

    int mousex = GetMouseX();
    int mousey = GetMouseY();

    switch(m_gamestate) {
        case GS_PLAYER_TURN:
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mousex >= 100 && mousey >= 250 && mousey <= 430) {
                int clickedcolumn = (mousex - 100) / 30;
                printf("column : %i\n", clickedcolumn);

                if(IsColumnFull(clickedcolumn) == false) {
                    PutInColumn(clickedcolumn, 1);

                    PacketContent p;
                    p.Append<char>(ID_PLAYED);
                    p.Append<char>(clickedcolumn);
                    enet_peer_send(m_peer, 0, p.MakePacket());
                }
            }
        break;

        default:
        break;
    }

}

void GameState::Draw() {
    switch(m_gamestate) {
        case GS_WAITING_PLAYER_CONNECTION:
            DrawText("Waiting for other player", 42, 42, 20, WHITE);
        break;

        case GS_OPPONENT_TURN:
        case GS_PLAYER_TURN:
            if(m_gamestate == GS_OPPONENT_TURN)
                DrawText("Opponent turn", 20, 20, 20, YELLOW);
            else
                DrawText("Your turn", 20, 20, 20, RED);
            DrawText("You are red", 20, 45, 20, RED);
            DrawGrid();
        break;

        default:
            DrawText("what", 42, 42, 20, RED);
        break;
    }
}

void GameState::OnReceive(ENetEvent& event) {
    unsigned char* pdata = event.packet->data;
    unsigned char packetid = pdata[0];

    switch(packetid) {
        case ID_WAITING_CONNECT:
            m_gamestate = GS_WAITING_PLAYER_CONNECTION;
        break;

        case ID_OTHER_PLAYED:
            {
                int column = pdata[1];
                PutInColumn(column, 2);
                m_gamestate = GS_PLAYER_TURN;
            }
        break;

        case ID_WAITING:
            m_gamestate = GS_OPPONENT_TURN;
        break;

        case ID_REQUEST_PLAY:
            m_gamestate = GS_PLAYER_TURN;
        break;

        case ID_OTHER_LEFT:
            m_manager->SetState(new MenuState("Other player left"));
        break;

        default:
            printf("Unknown packet id %x\n", packetid);
        break;
    }
}

void GameState::Set(int x, int y, char val) {
    if(x < 0) return;
    if(y < 0) return;
    if(x >= 7) return;
    if(y >= 6) return;

    m_grid[x+y*7] = val;
}

char GameState::Get(int x, int y) {
    if(x < 0) return -1;
    if(y < 0) return -1;
    if(x >= 7) return -1;
    if(y >= 6) return -1;

    return m_grid[x+y*7];
}

void GameState::PutInColumn(int column, char val) {
    if(column < 0) return;
    if(column >= 7) return;

    for(int y = 0; y < 6; y++) {
        if(Get(column, y) == 0) {
            Set(column, y, val);
            break;
        }
    }
}

bool GameState::IsColumnFull(int column) {
    if(column < 0) return true;
    if(column >= 7) return true;

    for(int y = 0; y < 6; y++) {
        if(Get(column, y) == 0) {
            return false;
        }
    }
    return true;
}


void GameState::DrawGrid() {
    for(int y = 0; y < 6; y++) {
        for(int x = 0; x < 7; x++) {
            DrawRectangleLines(100 + x*30, 400 - y*30, 30, 30, WHITE);
            DrawRectangle(100 + x*30 + 1, 400 - y*30 + 1, 30 - 2, 30 - 2, cols[Get(x, y)]);
        }
    }
}