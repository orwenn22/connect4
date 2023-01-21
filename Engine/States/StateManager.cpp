#include "StateManager.h"
#include "State.h"

StateManager::StateManager(Game* game, State* state) {
    m_game = game;
    m_isingame = true;
    SetState(state);
}

StateManager::StateManager(Game* game) {
    m_game = game;
    m_isingame = true;
    m_havestate = false;
}


StateManager::StateManager(State* state) {
    m_isingame = false;
    SetState(state);
}

StateManager::StateManager() {
    m_isingame = false;
    m_havestate = false;
}

StateManager::~StateManager() {
    DeleteState();
}


void StateManager::SetState(State* state) {
    DeleteState();
    m_state = state;
    m_havestate = true;

    m_state->m_manager = this;
    m_state->m_isinmanager = true;

    if(m_isingame) {
        m_state->m_game = m_game;
        m_state->m_isingame = true;
    }

    m_state->OnParrentAdd();
}

void StateManager::DeleteState() {
    if(m_havestate) {
        delete m_state;
        m_havestate = false;
    }
}

void StateManager::Update() {
    if(m_havestate) {
        m_state->UpdateP();
    }
}

void StateManager::Draw() {
    if(m_havestate) {
        m_state->DrawP();
    }
}