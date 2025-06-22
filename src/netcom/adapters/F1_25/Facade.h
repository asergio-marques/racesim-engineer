#ifndef NETCOM_ADAPTERS_INCLUDE_F1_25_H_
#define NETCOM_ADAPTERS_INCLUDE_F1_25_H_

#include <vector>
#include "adapters/Interface.h"
#include "adapters/SessionStateMachine.h"
#include "adapters/F1_25/SessionStartBuilder.h"



namespace Packet {

    namespace Game {

        class Interface;

        namespace F1_25 {

            class EventData;
            class LapData;
            struct LapHistoryInfo;
            class ParticipantData;
            class SessionData;
            class SessionHistoryData;

        }

    }

    namespace Internal {

        class Interface;

    }

}

namespace NetCom {

    namespace Adapter {

        namespace F1_25 {

            class Facade : public NetCom::Adapter::Interface {

                public:
                Facade();
                virtual ~Facade() = default;

                Packet::Game::Interface* ProcessDatagram(const char* datagram) override final;
                std::vector<Packet::Internal::Interface*> ConvertPacket(const Packet::Game::Interface* packet) override final;

                private:
                std::vector<Packet::Internal::Interface*> ConvertLapDataPacket(const Packet::Game::F1_25::LapData* inputPacket);
                std::vector<Packet::Internal::Interface*> ConvertEventDataPacket(const Packet::Game::F1_25::EventData* inputPacket);
                std::vector<Packet::Internal::Interface*> ConvertSessionDataPacket(const Packet::Game::F1_25::SessionData* inputPacket);
                std::vector<Packet::Internal::Interface*> ConvertParticipantDataPacket(const Packet::Game::F1_25::ParticipantData* inputPacket);
                std::vector<Packet::Internal::Interface*> ConvertSessionHistoryDataPacket(const Packet::Game::F1_25::SessionHistoryData* inputPacket);
                void AddLapStatusInfo(const uint8_t lapNo,
                    const Packet::Game::F1_25::LapHistoryInfo* inputInfo,
                    Packet::Internal::Interface* outputPacket) const;

                NetCom::Adapter::SessionStateMachine m_sessionSM;
                NetCom::Adapter::F1_25::SessionStartBuilder m_startPacketBuilder;

            };

        }

    }

}

#endif // NETCOM_ADAPTERS_INCLUDE_F1_25_H_