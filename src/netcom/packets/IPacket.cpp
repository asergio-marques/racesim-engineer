#include "netcom/packets/IPacket.h"
#include "general/data/PacketEnums.h"



F1_23::Packet::IPacket::IPacket(Header* header) :
    m_header(header) {

}



F1_23::Packet::IPacket::~IPacket() {
    
    delete m_header;

}