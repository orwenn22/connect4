#ifndef PACKETCONTENT_H
#define PACKETCONTENT_H

#include "enet/enet.h"

class PacketContent {
    public:
    PacketContent();
    ~PacketContent();

    void Expend();

    ENetPacket* MakePacket();
    void Print();


    //void Append(char data);
    //void Append(short data);
    //void Append(int data);

    template<typename T>
    void Append(T data) {
        int sizeofdata = sizeof(T);

        while(m_size + sizeofdata > m_allocsize) {
            Expend();
        }

        for(int i = sizeofdata-1; i >= 0; i--) {
            m_content[m_size] = (char) ((data >> (8*i)) & 0xff);
            m_size++;
        }
    }

    char* m_content;
    unsigned int m_size;
    unsigned int m_allocsize;
};

#endif