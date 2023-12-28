#ifndef NETCOM_ADAPTERS_INCLUDE_F123_H_
#define NETCOM_ADAPTERS_INCLUDE_F123_H_

#include "adapters/Interface.h"

namespace Packet {

    namespace Game {

        class Interface;

        namespace F1_23 {

            class EventData;
            class ParticipantData;
            class SessionData;

        }

    }

    namespace Internal {

        class Interface;

    }

}

namespace NetCom {

    namespace Adapter {

        class F1_23 : public NetCom::Adapter::Interface {

            public:
            F1_23();
            virtual ~F1_23() = default;

            Packet::Game::Interface* ProcessDatagram(const char* datagram) override final;
            const Packet::Internal::Interface* ConvertPacket(const Packet::Game::Interface* packet) override final;

            private:
            const Packet::Internal::Interface* ConvertEventDataPacket(const Packet::Game::F1_23::EventData* inputPacket);
            const Packet::Internal::Interface* ConvertSessionDataPacket(const Packet::Game::F1_23::SessionData* inputPacket);
            const Packet::Internal::Interface* ConvertParticipantDataPacket(const Packet::Game::F1_23::ParticipantData* inputPacket);

            bool m_sessionInProgress;
            bool m_sessionStartPacketSent;
            bool m_waitingForFirstSessionPacket;
            bool m_waitingForFirstParticipantPacket;
            Packet::Internal::Interface* m_sessionStartPacket;

        };

    }

}

#endif // NETCOM_ADAPTERS_INCLUDE_F123_H_