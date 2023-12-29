#ifndef NETCOM_ADAPTERS_INCLUDE_F123_H_
#define NETCOM_ADAPTERS_INCLUDE_F123_H_

#include "adapters/Interface.h"
#include "adapters/SessionStateMachine.h"
#include "adapters/F1_23/SessionStartBuilder.h"



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
            Packet::Internal::Interface* ConvertPacket(const Packet::Game::Interface* packet) override final;

            private:
            Packet::Internal::Interface* ConvertEventDataPacket(const Packet::Game::F1_23::EventData* inputPacket);
            Packet::Internal::Interface* ConvertSessionDataPacket(const Packet::Game::F1_23::SessionData* inputPacket);
            Packet::Internal::Interface* ConvertParticipantDataPacket(const Packet::Game::F1_23::ParticipantData* inputPacket);

            NetCom::Adapter::SessionStateMachine m_sessionSM;
            NetCom::Adapter::F1_23_SessionStartBuilder m_startPacketBuilder;

        };

    }

}

#endif // NETCOM_ADAPTERS_INCLUDE_F123_H_