#include "netcom/packet_builders/Header.h"

#include "netcom/packets/Header.h"
#include "core/data/Packet.h"
#include "netcom/packet_builders/Helper.h"



F1_23::PacketBuilder::Header::Header() {

}

F1_23::Packet::Header* F1_23::PacketBuilder::Header::buildNewHeader(char* packetInfo) const {

    F1_23::Packet::Header* newHeader = new F1_23::Packet::Header;
    size_t headerNumBytes = static_cast<size_t>(F1_23::Packet::LengthBytes::Header);

    // Current position in the array
    size_t arrayStatus = 0;

    // Get packet format
    F1_23::PacketBuilder::Helper::getVariableFromByteStream<>(packetInfo,
        &(newHeader->m_packetFormat),
        arrayStatus);

    // Get last two digits of game year
    F1_23::PacketBuilder::Helper::getVariableFromByteStream<>(packetInfo,
        &(newHeader->m_gameYear),
        arrayStatus);

    // Get major version of the game
    F1_23::PacketBuilder::Helper::getVariableFromByteStream<>(packetInfo,
        &(newHeader->m_gameMajorVersion),
        arrayStatus);

    // Get minor version of the game
    F1_23::PacketBuilder::Helper::getVariableFromByteStream<>(packetInfo,
        &(newHeader->m_gameMinorVersion),
        arrayStatus);

    // Get packet version
    F1_23::PacketBuilder::Helper::getVariableFromByteStream<>(packetInfo,
        &(newHeader->m_packetVersion),
        arrayStatus);

    // Get packet ID
    F1_23::PacketBuilder::Helper::getVariableFromByteStream<>(packetInfo,
        &(newHeader->m_packetId),
        arrayStatus);

    // Get session ID
    F1_23::PacketBuilder::Helper::getVariableFromByteStream<>(packetInfo,
        &(newHeader->m_sessionUID),
        arrayStatus);

    // Get timestamp for current session
    F1_23::PacketBuilder::Helper::getVariableFromByteStream<>(packetInfo,
        &(newHeader->m_sessionTime),
        arrayStatus);

    // Get ID for frame for which the current data corresponds
    F1_23::PacketBuilder::Helper::getVariableFromByteStream<>(packetInfo,
        &(newHeader->m_frameIdentifier),
        arrayStatus);

    // Get overall ID for frame ignoring flashbacks
    F1_23::PacketBuilder::Helper::getVariableFromByteStream<>(packetInfo,
        &(newHeader->m_overallFrameIdentifier),
        arrayStatus);

    // Get player 1 car index
    F1_23::PacketBuilder::Helper::getVariableFromByteStream<>(packetInfo,
        &(newHeader->m_carIndexPlayer1),
        arrayStatus);

    // Get player 2 car index
    F1_23::PacketBuilder::Helper::getVariableFromByteStream<>(packetInfo,
        &(newHeader->m_carIndexPlayer2),
        arrayStatus);

    return newHeader;

}