#include "converter/PacketGeneralizer.h"

#include "adapters/Interface.h"
#include "packets/Subscriber.h"
#include "packets/IPacket.h"



void NetCom::Converter::PacketGeneralizer::OnPacketBroadcast(const std::shared_ptr<Packet::IPacket> packet) {

    if (packet && m_gameAdapter) {
    
        auto pack = m_gameAdapter->ConvertPacket(packet.get());

    }

}



void NetCom::Converter::PacketGeneralizer::setGameAdapter(NetCom::Adapter::Interface* gameAdapter) {

    if (gameAdapter) {

        m_gameAdapter = gameAdapter;

    }

}