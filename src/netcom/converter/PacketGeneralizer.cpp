#include "converter/PacketGeneralizer.h"

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
    
        Packet::Internal::Interface* internalPacket = m_gameAdapter->ConvertPacket(gamePacket);

        if (internalPacket) {

            Broadcast(internalPacket);

        }

    }

}



void NetCom::Converter::PacketGeneralizer::setGameAdapter(NetCom::Adapter::Interface* gameAdapter) {

    if (gameAdapter) {

        m_gameAdapter = gameAdapter;

    }

}