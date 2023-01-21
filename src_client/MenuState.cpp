#include "MenuState.h"

#include "GameState.h"

#include <Engine/Engine.h>

#include <raylib.h>

#include <stdio.h>
#include <string>

int mystoi(char* str) {
    int r = 0;

    int i = 0;
    while(str[i] >= '0' && str[i] <= '9') {
        r *= 10;
        r += str[i] - '0';
        i++;
    }
    return r;
}


MenuState::MenuState(std::string splashtext) : State() {
    m_splashtext = splashtext;
    m_selectedfield = 0;
    m_ipfieldcount = 0;
    m_portfieldcount = 0;

    for(int i = 0; i < SIZE_OF_IP_FIELD+1; i++)
        m_ipfield[i] = 0;
    
    for(int i = 0; i < SIZE_OF_PORT_FIELD+1; i++)
        m_portfield[i] = 0;
}

void MenuState::Update() {
    if(IsKeyPressed(KEY_TAB)) {
        m_selectedfield++;
        if(m_selectedfield == 2)
            m_selectedfield = 0;
    }

    for(int key = KEY_KP_0; key <= KEY_KP_9; key++) {
        if(IsKeyPressed(key)) {
            InputCharacter(key-272);
        }
    }

    if(IsKeyPressed(KEY_BACKSPACE))
        InputCharacter(1);
    
    if(IsKeyPressed(KEY_KP_DECIMAL))
        InputCharacter('.');

    if(IsKeyPressed(KEY_ENTER)) {
        unsigned short port = mystoi(m_portfield);
        printf("port %i\n", port);
        m_manager->SetState(new GameState(m_ipfield, port));
    }
}

void MenuState::Draw() {
    DrawText("IP", 30, 62, 20, GRAY);
    DrawRectangleLines(60, 62, 200, 20, WHITE);
    DrawText(m_ipfield, 62, 62, 20, WHITE);

    DrawText("Port", 10, 88, 20, GRAY);
    DrawRectangleLines(60, 88, 200, 20, WHITE);
    DrawText(m_portfield, 62, 88, 20, WHITE);

    DrawText("<", 263, 62 + 26*m_selectedfield, 20, YELLOW);

    DrawText(m_splashtext.c_str(), 120, 120, 20, WHITE);
}


void MenuState::InputCharacter(char c) {
    char* field;
    int* fieldcount;
    int sizeoffield;

    if(m_selectedfield == 0) {  //IP
        field = m_ipfield;
        fieldcount = &m_ipfieldcount;
        sizeoffield = SIZE_OF_IP_FIELD;
    }
    else if(m_selectedfield == 1) {     //Port
        field = m_portfield;
        fieldcount = &m_portfieldcount;
        sizeoffield = SIZE_OF_PORT_FIELD;
    }

    if(c == 1) {
        if((*fieldcount) > 0) {
            (*fieldcount)--;
            field[*fieldcount] = 0;
        }
        return;
    }

    if((*fieldcount) >= sizeoffield) return;

    field[*fieldcount] = c;
    (*fieldcount)++;
} 