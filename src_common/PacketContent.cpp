#include "PacketContent.h"

#include <stdio.h>
#include <stdlib.h>

PacketContent::PacketContent() {
    m_content = (char*) malloc(sizeof(char) * 32);
    m_allocsize = 32;
    m_size = 0;
}

PacketContent::~PacketContent() {
    //printf("Destroyed packetcontent\n");
    free(m_content);
    m_allocsize = 0;
    m_size = 0;
}

void PacketContent::Expend() {
    m_content = (char* )realloc(m_content, m_allocsize*2);
    m_allocsize *= 2;
}

void PacketContent::Print() {
    for(int i = 0; i < m_size; i++) {
        printf("%x ", (unsigned char) m_content[i]);
    }
    printf("\n");
}

ENetPacket* PacketContent::MakePacket() {
    return enet_packet_create(m_content, m_size, ENET_PACKET_FLAG_RELIABLE);
}