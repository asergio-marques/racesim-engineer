#ifndef PACKETS_EVENT_INCLUDE_PRACTICE_START_H_
#define PACKETS_EVENT_INCLUDE_PRACTICE_START_H_

#include <cstdint>
#include <vector>
#include "data/internal/Session.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



namespace Packet {

    namespace Event {

        struct PracticeStart : public Packet::Event::Interface {

            public:
            // Packet constructor
            PracticeStart(const uint64_t timestamp);

            // Destructor
            virtual ~PracticeStart() = default;

            // Type identifier for the packet
            const Packet::Event::Type packetType() const override final;

            // Structure containing all relevant data about the track the session is taking place at
            Session::Internal::TrackInfo m_trackInfo;

            // List containing the initial data for all session participants
            std::vector<Session::Internal::Participant> m_participants;

            // Duration of the qualifying session (seconds)
            const uint16_t m_duration;

        };

    }

}

#endif  //  PACKETS_EVENT_INCLUDE_PRACTICE_START_H_