#include "Game.h"

#include "States/StateManager.h"

Game::Game() {
    m_statemanager = new StateManager(this);
    m_requestquit = false;

    //Default size
    SetScreenSize(512, 512);
    m_gamecamerablock = true;
}

Game::~Game() {
    delete m_statemanager;
}

void Game::Update() {
    m_statemanager->Update();
}

void Game::Draw() {
    m_statemanager->Draw();
}


void Game::SetState(State* state) {
    m_statemanager->SetState(state);
}

void Game::SetScreenSize(int width, int height) {
    m_gamewidth = width;
    m_gameheight = height;
}