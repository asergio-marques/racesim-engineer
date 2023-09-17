#include "netcom/packets/Header.h"

#include <cstdint>
#include <iostream>
#include <math.h>
#include "core/data/Packet.h"



F1_23::Packet::Header::Header() :
    m_packetFormat(0), 
    m_gameYear(0),
    m_gameMajorVersion(0),
    m_gameMinorVersion(0),
    m_packetVersion(0),
    m_packetId(F1_23::Packet::Type::InvalidUnknown),
    m_sessionUID(0),
    m_sessionTime(0.0f),
    m_frameIdentifier(0),
    m_overallFrameIdentifier(0),
    m_playerCarIndex(0),
    m_secondaryPlayerCarIndex(0) {

}

const F1_23::Packet::Type F1_23::Packet::Header::getPacketType() const {
    
    return m_packetId;

}
