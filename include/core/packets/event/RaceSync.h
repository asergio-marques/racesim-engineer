#ifndef PACKETS_EVENT_INCLUDE_RACE_SYNC_H_
#define PACKETS_EVENT_INCLUDE_RACE_SYNC_H_

#include <vector>
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"
#include "data/internal/Participant.h"
#include "data/internal/TyreData.h"
#include "data/internal/Session.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



namespace Packet {

    namespace Event {

        struct RaceSync : public Packet::Event::Interface {

            public:

            struct ParticipantData {

                // Index for this participant
                uint8_t m_index = 0;

                // Current status of the participant
                Participant::Internal::Status m_status = Participant::Internal::Status::InvalidUnknown;

                // Current position for this participant
                uint8_t m_currentPosition = 0;

                // Time for this driver's last lap
                Lap::Internal::Time m_lastLapTime;

                // Whether the last lap of this driver was a personal best, session best, or nothing special (lol)
                Lap::Internal::InfoType m_lastLapInfoType = Lap::Internal::InfoType::InvalidUnknown;

                // Time for this driver's best lap
                Lap::Internal::Time m_bestLapTime;

                // Whether the driver's best lap is a session best
                bool m_bestLapSessionBest;

                // List of all the stints done by the driver, from most recent tyres to first
                std::vector<Tyre::Internal::Data> m_tyreStints;

                // Total unserved time penalties accured by the participant, in milliseconds
                uint8_t m_totalTimePen;

                // Total unserved drive-through penalties accured by the participant
                uint8_t m_totalDriveThrough;
            };

            // Packet interface constructor
            RaceSync();

            // Destructor
            virtual ~RaceSync() = default;

            // Type identifier for the packet
            const Packet::Event::Type packetType() const override final;

            // List containing the initial data for all session participants
            std::vector<Packet::Event::RaceSync::ParticipantData> m_participants;

        };

    }

}

#endif  //  PACKETS_EVENT_INCLUDE_RACE_START_H_