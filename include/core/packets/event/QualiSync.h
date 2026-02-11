#ifndef PACKETS_EVENT_INCLUDE_QUALI_SYNC_H_
#define PACKETS_EVENT_INCLUDE_QUALI_SYNC_H_

#include <cstdint>
#include <map>
#include <vector>
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"
#include "data/internal/Participant.h"
#include "data/internal/Session.h"
#include "data/internal/Sector.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



namespace Packet {

    namespace Event {

        struct QualiSync : public Packet::Event::Interface {

            public:

            struct ParticipantData {

                // Index for this participant
                uint8_t m_index = 0;

                // Current status of the participant
                Participant::Internal::Status m_status = Participant::Internal::Status::InvalidUnknown;

                // Current position for this participant
                uint8_t m_currentPosition = 0;

                // Time for this driver's last lap
                Lap::Internal::Time m_lastLapTime{ 0 };

                // Whether the last lap of this driver was a personal best, session best, or nothing special (lol)
                Lap::Internal::InfoType m_lastLapInfoType = Lap::Internal::InfoType::InvalidUnknown;

                // Time for this driver's best lap
                Lap::Internal::Time m_bestLapTime{ 0 };

                // Whether the driver's best lap is a session best
                bool m_bestLapSessionBest = false;

                // A map holding all sectors of the current lap, mapped by lap order ID
                std::map<uint16_t, Lap::Internal::Sector> m_currentLapSectors{};

                // A map holding all minisectors of the current lap, mapped by lap order ID
                std::map<uint16_t, Lap::Internal::Sector> m_currentLapMinisectors{};

            };

            // Packet interface constructor
            QualiSync();

            // Destructor
            virtual ~QualiSync() = default;

            // Type identifier for the packet
            const Packet::Event::Type packetType() const override final;

            // List containing the initial data for all session participants
            std::vector<Packet::Event::QualiSync::ParticipantData> m_participants;

        };

    }

}

#endif  //  PACKETS_EVENT_INCLUDE_QUALI_SYNC_H_