#ifndef GENERALIZER_ADAPTERS_INCLUDE_F1_25_H_
#define GENERALIZER_ADAPTERS_INCLUDE_F1_25_H_

#include <string>
#include <vector>
#include "adapters/Interface.h"
#include "data/internal/Session.h"



namespace Packet {

    namespace Game {

        class Interface;

        namespace F1_25 {

            class CarStatusData;
            class LapData;
            struct LapHistoryInfo;
            class ParticipantData;
            class ParticipantInfo;
            class SessionData;
            class SessionHistoryData;
            class TyreSetData;

        }

    }

    namespace Internal {

        class Interface;

    }

}

namespace Generalizer {

    namespace Adapter {

        class F1_25 : public Generalizer::Adapter::Interface {

            public:
            F1_25() = default;
            virtual ~F1_25() = default;
            std::vector<Packet::Internal::Interface*> ConvertPacket(const Packet::Game::Interface* packet) override final;

            private:
            std::vector<Packet::Internal::Interface*> ConvertSessionDataPacket(const Packet::Game::F1_25::SessionData* inputPacket);
            std::vector<Packet::Internal::Interface*> ConvertLapDataPacket(const Packet::Game::F1_25::LapData* inputPacket);
            std::vector<Packet::Internal::Interface*> ConvertCarStatusDataPacket(const Packet::Game::F1_25::CarStatusData* inputPacket);
            std::vector<Packet::Internal::Interface*> ConvertParticipantDataPacket(const Packet::Game::F1_25::ParticipantData* inputPacket);
            std::vector<Packet::Internal::Interface*> ConvertSessionHistoryDataPacket(const Packet::Game::F1_25::SessionHistoryData* inputPacket);
            std::vector<Packet::Internal::Interface*> ConvertTyreSetDataPacket(const Packet::Game::F1_25::TyreSetData* inputPacket);
            void AddLapStatusInfo(const uint8_t lapNo,
                const Packet::Game::F1_25::LapHistoryInfo* inputInfo,
                Packet::Internal::Interface* outputPacket) const;

            // Auxiliary functions
            const std::string ShortenDriverName(const char* originalName);
            const Session::Internal::Participant GetSingleParticipantData(const Packet::Game::F1_25::ParticipantInfo& rawInfo,
                const uint8_t& arrayIndex,
                const uint8_t& playerIndex);
            void ExtractSessionSettings(const Packet::Game::F1_25::SessionData* inputPacket,
                Session::Internal::TrackInfo& trackInfo,
                Session::Internal::Settings& settings);

        };

    }

}

#endif // GENERALIZER_ADAPTERS_INCLUDE_F1_25_H_