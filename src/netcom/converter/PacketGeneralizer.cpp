#include "converter/PacketGeneralizer.h"

#include <vector>
#include "adapters/Interface.h"
#include "packets/internal/Interface.h"
#include "packets/game/Subscriber.h"
#include "packets/game/Interface.h"



NetCom::Converter::PacketGeneralizer::PacketGeneralizer() :
    Packet::Game::Subscriber(),
    Packet::Internal::Broadcaster(),
    m_gameAdapter(nullptr) {



}



void NetCom::Converter::PacketGeneralizer::OnPacketBroadcast(Packet::Game::Interface* gamePacket) {

    if (gamePacket && m_gameAdapter) {
    
        std::vector<Packet::Internal::Interface*> newPackets = m_gameAdapter->ConvertPacket(gamePacket);
        for (auto packet : newPackets) {

            if (packet) Broadcast(packet);

        }

    }

}



void NetCom::Converter::PacketGeneralizer::setGameAdapter(NetCom::Adapter::Interface* gameAdapter) {

    if (gameAdapter) {

        m_gameAdapter = gameAdapter;

    }

}