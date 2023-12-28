#ifndef NETCOM_CONVERTER_INCLUDE_PACKET_GENERALIZER_H_
#define NETCOM_CONVERTER_INCLUDE_PACKET_GENERALIZER_H_

#include "packets/internal/Broadcaster.h"
#include "packets/game/Subscriber.h"



namespace Packet {

    class Interface;

}

namespace NetCom {

    namespace Adapter {

        class Interface;

    }

    namespace Converter {

        class PacketGeneralizer : public Packet::Game::Subscriber, public Packet::Internal::Broadcaster {

            public:
            PacketGeneralizer();
            ~PacketGeneralizer() = default;

            // Interface function called when a new packet is available
            void OnPacketBroadcast(Packet::Game::Interface* gamePacket) override final;

            // Inject the game adapter object from above, being managed by a higher-level component
            void setGameAdapter(NetCom::Adapter::Interface* gameAdapter);

            private:
            NetCom::Adapter::Interface* m_gameAdapter;

        };

    }

}

#endif // NETCOM_CONVERTER_INCLUDE_PACKET_GENERALIZER_H_