#ifndef NETCOM_ADAPTERS_INCLUDE_F123_SESSION_START_BUILDER_H_
#define NETCOM_ADAPTERS_INCLUDE_F123_SESSION_START_BUILDER_H_

#include <vector>
#include <map>
#include <string>
#include "data/internal/Session.h"



namespace Packet {

    namespace Internal {

        class PracticeStart;
        class QualiStart;
        class RaceStart;
        class SessionStart;
        class TimeTrialStart;

    }

    namespace Game {

        namespace F1_23 {

            class ParticipantData;
            class ParticipantInfo;
            class SessionData;
            class LapData;

        }

    }

}

namespace NetCom {

    namespace Adapter {

        class F1_23_SessionStartBuilder {

            public:
            F1_23_SessionStartBuilder();
            virtual ~F1_23_SessionStartBuilder() = default;

            void Start();
            void CreateSessionPacket(const Packet::Game::F1_23::SessionData* gamePacket);
            void AppendParticipantData(const Packet::Game::F1_23::ParticipantData* gamePacket);
            void AppendLapData(const Packet::Game::F1_23::LapData* gamePacket);
            Packet::Internal::SessionStart* Finish();

            private:
            // Main creation functions
            Packet::Internal::TimeTrialStart* CreateTimeTrialStartPacket(const Packet::Game::F1_23::SessionData* gamePacket);
            Packet::Internal::PracticeStart* CreatePracticeStartPacket(const Packet::Game::F1_23::SessionData* gamePacket);
            Packet::Internal::QualiStart* CreateQualiStartPacket(const Packet::Game::F1_23::SessionData* gamePacket, uint8_t numClassifiedAtEnd);
            Packet::Internal::RaceStart* CreateRaceStartPacket(const Packet::Game::F1_23::SessionData* gamePacket);

            // Auxiliary functions for duplicated code
            void ConvertTrackID(Packet::Internal::SessionStart* newPacket, const Packet::Game::F1_23::SessionData* gamePacket);
            const std::string ShortenDriverName(const char* originalName);
            const Session::Internal::Participant GetSingleParticipantData(const Packet::Game::F1_23::ParticipantInfo& rawInfo,
                const uint8_t& arrayIndex,
                const uint8_t& playerIndex);
            
            bool m_enabled;
            bool m_waitingForParticipantData;
            bool m_waitingForSessionData;
            bool m_waitingForLapData;

            Packet::Internal::SessionStart* m_packetBeingBuilt;
            std::vector<Session::Internal::Participant> m_listParticipants;

        };

    }

}

#endif // NETCOM_ADAPTERS_INCLUDE_F123_SESSION_START_BUILDER_H_