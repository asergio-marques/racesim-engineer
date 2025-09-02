#ifndef PACKETS_EVENT_INCLUDE_QUALI_START_H_
#define PACKETS_EVENT_INCLUDE_QUALI_START_H_

#include <cstdint>
#include <vector>
#include "data/internal/Session.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



namespace Packet {

    namespace Event {

        struct QualiStart : public Packet::Event::Interface {

            // Packet constructor
            QualiStart(uint8_t carsClassifiedAtEnd);

            // Destructor
            virtual ~QualiStart() = default;

            // Type identifier for the packet
            const Packet::Event::Type packetType() const override final;

            // Structure containing all relevant data about the track the session is taking place at
            Session::Internal::TrackInfo m_trackInfo;

            // List containing the initial data for all session participants
            std::vector<Session::Internal::Participant> m_participants;

            // Duration of the qualifying session (seconds)
            const uint16_t m_duration;

            // How many participants are qualified to this session
            const uint8_t m_noActiveParticipants;

            // How many participants are qualified to the next session
            const uint8_t m_noNextSessionParticipants;

        };

    }

}

#endif  //  PACKETS_EVENT_INCLUDE_QUALI_START_H_