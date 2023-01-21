#ifndef GAME_H
#define GAME_H

class State;
class StateManager;

class Game {
    public:
    Game();
    virtual ~Game();

    void Update();
    void Draw();

    //this is a shortcut to m_statemanager->SetState(state)
    void SetState(State* state);
    
    void SetScreenSize(int width, int height);


    StateManager* m_statemanager;

    bool m_requestquit;

    //used by RoomState
    int m_gamewidth;
    int m_gameheight;
    bool m_gamecamerablock;
};

#endif