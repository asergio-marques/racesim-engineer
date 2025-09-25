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

            class LapData;
            struct LapHistoryInfo;
            class ParticipantData;
            class ParticipantInfo;
            class SessionData;
            class SessionHistoryData;
            class StandingsData;

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
            std::vector<std::shared_ptr<Packet::Internal::Interface>> ConvertPacket(std::shared_ptr<Packet::Game::Interface> packet) override final;

            private:
            std::vector<std::shared_ptr<Packet::Internal::Interface>> ConvertSessionDataPacket(std::shared_ptr < Packet::Game::F1_25::SessionData> inputPacket);
            std::vector<std::shared_ptr<Packet::Internal::Interface>> ConvertLapDataPacket(std::shared_ptr<Packet::Game::F1_25::LapData> inputPacket);
            std::vector<std::shared_ptr<Packet::Internal::Interface>> ConvertParticipantDataPacket(std::shared_ptr<Packet::Game::F1_25::ParticipantData> inputPacket);
            std::vector<std::shared_ptr<Packet::Internal::Interface>> ConvertStandingsDataPacket(std::shared_ptr<Packet::Game::F1_25::StandingsData> inputPacket);
            std::vector<std::shared_ptr<Packet::Internal::Interface>> ConvertSessionHistoryDataPacket(std::shared_ptr<Packet::Game::F1_25::SessionHistoryData> inputPacket);
            void AddLapStatusInfo(const uint8_t lapNo,
                const Packet::Game::F1_25::LapHistoryInfo* inputInfo,
                std::shared_ptr<Packet::Internal::Interface> outputPacket) const;

            // Auxiliary functions
            const std::string ShortenDriverName(const char* originalName, uint8_t driverID);
            const Session::Internal::Participant GetSingleParticipantData(const Packet::Game::F1_25::ParticipantInfo& rawInfo,
                const uint8_t& arrayIndex,
                const uint8_t& playerIndex);
            void ExtractSessionSettings(std::shared_ptr<Packet::Game::F1_25::SessionData> inputPacket,
                Session::Internal::TrackInfo& trackInfo,
                Session::Internal::Settings& settings);

        };

    }

}

#endif // GENERALIZER_ADAPTERS_INCLUDE_F1_25_H_