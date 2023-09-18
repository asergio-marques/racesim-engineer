#include "packets/IPacket.h"

#include <iostream>
#include "packets/Header.h"
#include "data/Packet.h"



F1_23::Packet::IPacket::IPacket() :
    m_header(nullptr) {

}



F1_23::Packet::IPacket::~IPacket() {
    
    if (m_header) { delete m_header; }

}



const F1_23::Packet::Header* F1_23::Packet::IPacket::getHeader() const {

    return m_header;

}