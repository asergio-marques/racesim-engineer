#include "packets/Header.h"

#include <cstdint>
#include <iostream>
#include <math.h>
#include "data/Packet.h"
#include "packets/Helper.h"



F1_23::Packet::Header::Header(char* packetInfo, F1_23::Packet::Helper* helper) :
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

    if (packetInfo && helper) {

        // Current position in the array
        size_t arrayStatus = 0;

        // Get packet format
        helper->getVariableFromByteStream<>(packetInfo, &m_packetFormat, arrayStatus);

        // Get last two digits of game year
        helper->getVariableFromByteStream<>(packetInfo, &m_gameYear, arrayStatus);

        // Get major version of the game
        helper->getVariableFromByteStream<>(packetInfo, &m_gameMajorVersion, arrayStatus);

        // Get minor version of the game
        helper->getVariableFromByteStream<>(packetInfo, &m_gameMinorVersion, arrayStatus);

        // Get packet version
        helper->getVariableFromByteStream<>(packetInfo, &m_packetVersion, arrayStatus);

        // Get packet ID
        helper->getVariableFromByteStream<>(packetInfo, &m_packetId, arrayStatus);

        // Get session ID
        helper->getVariableFromByteStream<>(packetInfo, &m_sessionUID, arrayStatus);

        // Get timestamp for current session
        helper->getVariableFromByteStream<>(packetInfo, &m_sessionTime, arrayStatus);

        // Get ID for frame for which the current data corresponds
        helper->getVariableFromByteStream<>(packetInfo, &m_frameIdentifier, arrayStatus);

        // Get overall ID for frame ignoring flashbacks
        helper->getVariableFromByteStream<>(packetInfo, &m_overallFrameIdentifier, arrayStatus);

        // Get player 1 car index
        helper->getVariableFromByteStream<>(packetInfo, &m_carIndexPlayer1, arrayStatus);

        // Get player 2 car index
        helper->getVariableFromByteStream<>(packetInfo, &m_carIndexPlayer2, arrayStatus);

    }
    else {
    
        // TODO proper error handling/exception
    
    }

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