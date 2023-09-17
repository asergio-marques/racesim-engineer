#include "netcom/packets/IPacket.h"

#include <iostream>
#include "netcom/packets/Header.h"
#include "core/data/Packet.h"



F1_23::Packet::IPacket::IPacket() :
    m_header(new F1_23::Packet::Header) {

}



F1_23::Packet::IPacket::~IPacket() {
    
    if (m_header) { delete m_header; }

}



const F1_23::Packet::Header* F1_23::Packet::IPacket::getHeader() const {

    return m_header;

}