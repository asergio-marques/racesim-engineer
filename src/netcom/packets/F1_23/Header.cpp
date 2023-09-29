#include "packets/F1_23/Header.h"

#include <cstdint>
#include <iostream>
#include <math.h>
#include "data/F1_23/Packet.h"
#include "packets/Helper.h"



Packet::F1_23::Header::Header(const char* packetInfo, Packet::Helper* helper) :
    m_packetFormat(0), 
    m_gameYear(0),
    m_gameMajorVersion(0),
    m_gameMinorVersion(0),
    m_packetVersion(0),
    m_packetType(Packet::F1_23::Type::InvalidUnknown),
    m_sessionUID(0),
    m_sessionTime(0.0f),
    m_frameIdentifier(0),
    m_overallFrameIdentifier(0),
    m_carIndexPlayer1(0),
    m_carIndexPlayer2(0) {

    if (packetInfo && helper) {

        // Current position in the array
        size_t arrayStatus = 0;

        helper->getVariableFromByteStream<>(packetInfo, &m_packetFormat, arrayStatus);
        helper->getVariableFromByteStream<>(packetInfo, &m_gameYear, arrayStatus);
        helper->getVariableFromByteStream<>(packetInfo, &m_gameMajorVersion, arrayStatus);
        helper->getVariableFromByteStream<>(packetInfo, &m_gameMinorVersion, arrayStatus);
        helper->getVariableFromByteStream<>(packetInfo, &m_packetVersion, arrayStatus);
        helper->getVariableFromByteStream<>(packetInfo, &m_packetType, arrayStatus);
        helper->getVariableFromByteStream<>(packetInfo, &m_sessionUID, arrayStatus);
        helper->getVariableFromByteStream<>(packetInfo, &m_sessionTime, arrayStatus);
        helper->getVariableFromByteStream<>(packetInfo, &m_frameIdentifier, arrayStatus);
        helper->getVariableFromByteStream<>(packetInfo, &m_overallFrameIdentifier, arrayStatus);
        helper->getVariableFromByteStream<>(packetInfo, &m_carIndexPlayer1, arrayStatus);
        helper->getVariableFromByteStream<>(packetInfo, &m_carIndexPlayer2, arrayStatus);

    }
    else {
    
        // TODO proper error handling/exception
    
    }

    if (helper) {
        
        // It is the responsability of the header to delete
        // the helper as it is to be used only for this function
        delete helper;

    }

}



const bool Packet::F1_23::Header::IsWellFormed() const {

    if ((GetPacketFormat() == 2023) &&
        (GetGameYear() == 0x17) &&
        (GetPacketVersion() > 0) &&
        (GetPacketType() != Packet::F1_23::Type::InvalidUnknown)) {

        return true;

    }

    return false;

}



#ifndef NDEBUG
void Packet::F1_23::Header::Print() const {
    
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "\tHeader info" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "Packet format: " << GetPacketFormat() << std::endl;
    std::cout << "Game year: " << static_cast<uint16_t>(GetGameYear()) << std::endl;
    std::cout << "Game major version: " << static_cast<uint16_t>(GetGameMajorVersion()) << std::endl;
    std::cout << "Game minor version: " << static_cast<uint16_t>(GetGameMinorVersion()) << std::endl;
    std::cout << "Packet version: " << static_cast<uint16_t>(GetPacketVersion()) << std::endl;
    std::cout << "Packet type ID: " << static_cast<uint16_t>(GetPacketType()) << std::endl;
    std::cout << "Session UUID: " << GetSessionUID() << std::endl;
    std::cout << "Session timestamp: " << GetSessionTime() << std::endl;
    std::cout << "Frame ID: " << GetFrameIdentifier() << std::endl;
    std::cout << "Overall frame ID: " << GetOverallFrameIdentifier() << std::endl;
    std::cout << "Player 1 index: " << static_cast<uint16_t>(GetCarIndexPlayer1()) << std::endl;
    std::cout << "Player 2 index: " << static_cast<uint16_t>(GetCarIndexPlayer2()) << std::endl;
    
}
#endif // NDEBUG