#ifndef MENU_STATE_H
#define MENU_STATE_H

#define SIZE_OF_IP_FIELD    15
#define SIZE_OF_PORT_FIELD  5

#include "Engine/States/State.h"

#include <string>

class MenuState : public State {
    public:
    MenuState(std::string splashtext);

    void Update() override;
    void Draw() override;


    void InputCharacter(char c);


    char m_ipfield[SIZE_OF_IP_FIELD+1];
    char m_portfield[SIZE_OF_PORT_FIELD+1];

    int m_ipfieldcount;
    int m_portfieldcount;

    unsigned char m_selectedfield;  // 0 = ip ; 1 = port


    std::string m_splashtext;
};

#endif