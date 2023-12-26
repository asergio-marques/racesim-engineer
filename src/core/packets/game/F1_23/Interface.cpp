#include "packets/game/F1_23/Interface.h"

#include <iostream>
#include "data/F1_23/Packet.h"
#include "packets/game/Helper.h"
#include "packets/game/F1_23/Header.h"



Packet::Game::F1_23::Interface::Interface() :
    m_header(nullptr) {

}



Packet::Game::F1_23::Interface::~Interface() {
    
    if (m_header) { delete m_header; }

}



const Packet::Game::F1_23::Header* Packet::Game::F1_23::Interface::GetHeader() const {

    return m_header;

}



bool Packet::Game::F1_23::Interface::SetHeader(const Packet::Game::F1_23::Header* header) {

    if (header && !m_header) {

        m_header = header;
        return true;

    }

    return false;

}