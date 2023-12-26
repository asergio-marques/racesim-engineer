#include "converter/PacketGeneralizer.h"

#include "adapters/Interface.h"
#include "packets/game/Subscriber.h"
#include "packets/game/Interface.h"



void NetCom::Converter::PacketGeneralizer::OnPacketBroadcast(const std::shared_ptr<Packet::Game::Interface> packet) {

    if (packet && m_gameAdapter) {
    
        auto pack = m_gameAdapter->ConvertPacket(packet.get());

    }

}



void NetCom::Converter::PacketGeneralizer::setGameAdapter(NetCom::Adapter::Interface* gameAdapter) {

    if (gameAdapter) {

        m_gameAdapter = gameAdapter;

    }

}