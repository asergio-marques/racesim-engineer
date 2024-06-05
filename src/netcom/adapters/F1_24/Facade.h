#ifndef NETCOM_ADAPTERS_INCLUDE_F124_H_
#define NETCOM_ADAPTERS_INCLUDE_F124_H_

#include <vector>
#include "adapters/Interface.h"
#include "adapters/SessionStateMachine.h"
#include "adapters/F1_24/SessionStartBuilder.h"



namespace Packet {

    namespace Game {

        class Interface;

        namespace F1_24 {

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

        namespace F1_24 {

            class Facade : public NetCom::Adapter::Interface {

                public:
                Facade();
                virtual ~Facade() = default;

                Packet::Game::Interface* ProcessDatagram(const char* datagram) override final;
                std::vector<Packet::Internal::Interface*> ConvertPacket(const Packet::Game::Interface* packet) override final;

                private:
                std::vector<Packet::Internal::Interface*> ConvertLapDataPacket(const Packet::Game::F1_24::LapData* inputPacket);
                std::vector<Packet::Internal::Interface*> ConvertEventDataPacket(const Packet::Game::F1_24::EventData* inputPacket);
                std::vector<Packet::Internal::Interface*> ConvertSessionDataPacket(const Packet::Game::F1_24::SessionData* inputPacket);
                std::vector<Packet::Internal::Interface*> ConvertParticipantDataPacket(const Packet::Game::F1_24::ParticipantData* inputPacket);

                NetCom::Adapter::SessionStateMachine m_sessionSM;
                NetCom::Adapter::F1_24::SessionStartBuilder m_startPacketBuilder;

            };

        }

    }

}

#endif // NETCOM_ADAPTERS_INCLUDE_F124_H_