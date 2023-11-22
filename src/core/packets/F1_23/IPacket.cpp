#include "packets/F1_23/IPacket.h"

#include <iostream>
#include "data/F1_23/Packet.h"
#include "packets/Helper.h"
#include "packets/F1_23/Header.h"



Packet::F1_23::IPacket::IPacket() :
    m_header(nullptr) {

}



Packet::F1_23::IPacket::~IPacket() {
    
    if (m_header) { delete m_header; }

}



const Packet::F1_23::Header* Packet::F1_23::IPacket::GetHeader() const {

    return m_header;

}



bool Packet::F1_23::IPacket::SetHeader(const Packet::F1_23::Header* header) {

    if (header && !m_header) {

        m_header = header;
        return true;

    }

    return false;

}