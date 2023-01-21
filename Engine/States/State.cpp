#include "State.h"
#include "StateManager.h"


#include <raylib.h>

State::State() {
    m_isinmanager = false;
    m_havesubstate = false;

    m_issubstate = false;
    m_blockparrentupdate = false;
    m_blockparrentdraw = false;

    m_isingame = false;
}

State::~State() {
    ClearSubState();
}

void State::SetSubState(State* state) {
    ClearSubState();
    m_substate = state;
    m_havesubstate = true;

    m_substate->m_parrentstate = this;
    m_substate->m_issubstate = true;

    if(m_isingame) {
        m_substate->m_game = m_game;
        m_substate->m_isingame = true;
    }

    m_substate->OnParrentAdd();
}

void State::ClearSubState() {
    if(m_havesubstate) {
        delete m_substate;
        m_havesubstate = false;
    }
}

void State::OnParrentAdd() {};

void State::Update() {}

void State::Draw() {}


void State::UpdateP() {
    if(m_havesubstate) {
        if(m_substate->m_blockparrentupdate == false) {
            Update();
        }
        m_substate->UpdateP();
    } else {
        Update();
    }
}

void State::DrawP() {
    if(m_havesubstate) {
        if(m_substate->m_blockparrentdraw == false) {
            Draw();
        }
        m_substate->DrawP();
    } else {
        Draw();
    }
}