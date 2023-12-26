#ifndef NETCOM_CONVERTER_INCLUDE_PACKET_GENERALIZER_H_
#define NETCOM_CONVERTER_INCLUDE_PACKET_GENERALIZER_H_

#include "packets/Subscriber.h"



namespace Packet {

    class IPacket;

}

namespace NetCom {

    namespace Adapter {

        class Interface;

    }

    namespace Converter {

        class PacketGeneralizer : public Packet::Subscriber {

            public:
            PacketGeneralizer() = default;
            ~PacketGeneralizer() = default;

            // Interface function called when a new packet is available
            void OnPacketBroadcast(const std::shared_ptr<Packet::IPacket> packet) override final;

            // Inject the game adapter object from above, being managed by a higher-level component
            void setGameAdapter(NetCom::Adapter::Interface* gameAdapter);

            private:
            NetCom::Adapter::Interface* m_gameAdapter;

        };

    }

}

#endif // NETCOM_CONVERTER_INCLUDE_PACKET_GENERALIZER_H_