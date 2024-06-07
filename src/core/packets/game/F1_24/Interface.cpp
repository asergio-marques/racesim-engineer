#include "packets/game/F1_24/Interface.h"

#include <iostream>
#include "data/game/F1_24/Packet.h"
#include "packets/game/Helper.h"
#include "packets/game/F1_24/Header.h"



Packet::Game::F1_24::Interface::Interface() :
    m_header(nullptr) {

}



Packet::Game::F1_24::Interface::~Interface() {
    
    if (m_header) { delete m_header; }

}



const Packet::Game::F1_24::Header* Packet::Game::F1_24::Interface::GetHeader() const {

    return m_header;

}



const Packet::Game::F1_24::LengthBytes Packet::Game::F1_24::Interface::GetLength() const {

    return Packet::Game::F1_24::LengthBytes::Header;

}



#ifndef NDEBUG
void Packet::Game::F1_24::Interface::Print() const {

    if (m_header) {

        m_header->Print();

    }

}
#endif // NDEBUG



bool Packet::Game::F1_24::Interface::SetHeader(const Packet::Game::F1_24::Header* header) {

    if (header && !m_header) {

        m_header = header;
        return true;

    }

    return false;

}



void Packet::Game::F1_24::Interface::BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) {

    // DO NOTHING

}