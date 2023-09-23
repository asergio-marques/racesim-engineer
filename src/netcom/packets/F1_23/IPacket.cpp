#include "packets/F1_23/IPacket.h"

#include <iostream>
#include "data/F1_23/Packet.h"
#include "packets/Helper.h"
#include "packets/F1_23/Header.h"



Packet::F1_23::IPacket::IPacket(char* packetInfo) :
    m_header(
        new Packet::F1_23::Header(packetInfo, new Packet::Helper(static_cast<size_t>(Packet::F1_23::LengthBytes::Header)))) {

}



Packet::F1_23::IPacket::~IPacket() {
    
    if (m_header) { delete m_header; }

}



const Packet::F1_23::Header* Packet::F1_23::IPacket::GetHeader() const {

    return m_header;

}