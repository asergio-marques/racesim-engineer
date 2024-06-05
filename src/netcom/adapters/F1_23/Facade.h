#ifndef NETCOM_ADAPTERS_INCLUDE_F123_H_
#define NETCOM_ADAPTERS_INCLUDE_F123_H_

#include <vector>
#include "adapters/Interface.h"
#include "adapters/SessionStateMachine.h"
#include "adapters/F1_23/SessionStartBuilder.h"



namespace Packet {

    namespace Game {

        class Interface;

        namespace F1_23 {

            class EventData;
            class LapData;
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

        namespace F1_23 {

            class Facade : public NetCom::Adapter::Interface {

                public:
                Facade();
                virtual ~Facade() = default;

                Packet::Game::Interface* ProcessDatagram(const char* datagram) override final;
                std::vector<Packet::Internal::Interface*> ConvertPacket(const Packet::Game::Interface* packet) override final;

                private:
                std::vector<Packet::Internal::Interface*> ConvertLapDataPacket(const Packet::Game::F1_23::LapData* inputPacket);
                std::vector<Packet::Internal::Interface*> ConvertEventDataPacket(const Packet::Game::F1_23::EventData* inputPacket);
                std::vector<Packet::Internal::Interface*> ConvertSessionDataPacket(const Packet::Game::F1_23::SessionData* inputPacket);
                std::vector<Packet::Internal::Interface*> ConvertParticipantDataPacket(const Packet::Game::F1_23::ParticipantData* inputPacket);

                NetCom::Adapter::SessionStateMachine m_sessionSM;
                NetCom::Adapter::F1_23::SessionStartBuilder m_startPacketBuilder;

            };

        }

    }

}

#endif // NETCOM_ADAPTERS_INCLUDE_F123_H_