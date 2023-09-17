#include "netcom/packet_builders/Header.h"

#include "netcom/packets/Header.h"
#include "core/data/Packet.h"



F1_23::PacketBuilder::Header::Header() {

}

F1_23::Packet::Header* F1_23::PacketBuilder::Header::buildNewHeader(char* packetInfo) const {

    F1_23::Packet::Header* newHeader = new F1_23::Packet::Header;
    size_t headerNumBytes = static_cast<size_t>(F1_23::Packet::LengthBytes::Header);

    // Current position in the array
    size_t arrayStatus = 0;

    // Get packet format
    //getVariable<>(packetInfo, newHeader->m_packetFormat, arrayStatus);

    return newHeader;

}