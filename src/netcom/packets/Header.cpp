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
    m_carIndexPlayer1(0),
    m_carIndexPlayer2(0) {

}

const F1_23::Packet::Type F1_23::Packet::Header::getPacketType() const {
    
    return m_packetId;

}

#ifndef NDEBUG
void F1_23::Packet::Header::print() const {
    std::cout << "Packet format: " << this->m_packetFormat << std::endl;
    std::cout << "Game year: " << static_cast<uint16_t>(this->m_gameYear) << std::endl;
    std::cout << "Game major version: " << static_cast<uint16_t>(this->m_gameMajorVersion) << std::endl;
    std::cout << "Game minor version: " << static_cast<uint16_t>(this->m_gameMinorVersion) << std::endl;
    std::cout << "Packet version: " << static_cast<uint16_t>(this->m_packetVersion) << std::endl;
    std::cout << "Packet type ID: " << static_cast<uint16_t>(this->m_packetId) << std::endl;
    std::cout << "Session UUID: " << this->m_sessionUID << std::endl;
    std::cout << "Session timestamp: " << this->m_sessionTime << std::endl;
    std::cout << "Frame ID: " << this->m_frameIdentifier << std::endl;
    std::cout << "Overall frame ID: " << this->m_overallFrameIdentifier << std::endl;
    std::cout << "Player 1 index: " << static_cast<uint16_t>(this->m_carIndexPlayer1) << std::endl;
    std::cout << "Player 2 index: " << static_cast<uint16_t>(this->m_carIndexPlayer2) << std::endl;
}
#endif // NDEBUG