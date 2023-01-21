#ifndef STATEMANAGER_H
#define STATEMANAGER_H

class Game;
class State;

class StateManager {
    public:
    StateManager(Game* game, State* state);
    StateManager(Game* game);
    StateManager(State* state);
    StateManager();

    ~StateManager();


    void SetState(State* state);
    void DeleteState();

    void Update();
    void Draw();

    //////////////////////////

    State* m_state;
    bool m_havestate;

    Game* m_game;
    bool m_isingame;
};

#endif