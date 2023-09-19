#include "packets/IPacket.h"

#include <iostream>
#include "packets/Header.h"
#include "packets/Helper.h"
#include "data/Packet.h"



F1_23::Packet::IPacket::IPacket(char* packetInfo) :
    m_header(
        new F1_23::Packet::Header(packetInfo, new F1_23::Packet::Helper(F1_23::Packet::LengthBytes::Header))) {

}



F1_23::Packet::IPacket::~IPacket() {
    
    if (m_header) { delete m_header; }

}



const F1_23::Packet::Header* F1_23::Packet::IPacket::getHeader() const {

    return m_header;

}