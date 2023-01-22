#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <DefaultClient.h>

#include <Engine/States/State.h>

enum GameStatesID {
    GS_WAITING_PLAYER_CONNECTION,
    GS_PLAYER_TURN,
    GS_OPPONENT_TURN
};

class GameState : public State , public DefaultClient {
    public:
    GameState(char* hostName, unsigned short port);

    void OnParrentAdd() override;
    void Update() override;
    void Draw() override;

    void ClientOnReceive(ENetEvent& event) override;

    void Set(int x, int y, char val);
    char Get(int x, int y);
    void PutInColumn(int column, char val);
    bool IsColumnFull(int column);

    void DrawGrid();


    char m_grid[7*6];
    int m_gamestate;
};

#endif