#ifndef STATE_H
#define STATE_H

#include <vector>

class Game;
class StateManager;

typedef struct Rectangle Rectangle;

class State {
    public:
    State();
    virtual ~State();

    void SetSubState(State* state);
    void ClearSubState();

    ////user-redefinable.
    //Called by StateManager::SetState() or State::SetSubState()
    virtual void OnParrentAdd();
    virtual void Update();
    virtual void Draw();

    //called by parrent (manager or parrent state).
    void UpdateP();
    void DrawP();


    ///////////////////////////

    //parrent manager.
    StateManager* m_manager;        //modified by StateManager::SetState
    bool m_isinmanager;             //^^^

    //parrent state.
    State* m_parrentstate;          //modified by State::SetSubState
    bool m_issubstate;              //^^^
    bool m_blockparrentupdate;      //if this is set to true, the perrent state's update method won't be executed
    bool m_blockparrentdraw;        //if this is set to true, the perrent state's draw method won't be executed

    //substate.
    State* m_substate;
    bool m_havesubstate;

    //Contain a pointer to the game
    Game* m_game;                   //potentially given by StateManager::SetState() or State::SetSubState()
    bool m_isingame;                //^^^
};

#endif