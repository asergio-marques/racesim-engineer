#ifndef PACKETS_EVENT_INCLUDE_RACE_START_H_
#define PACKETS_EVENT_INCLUDE_RACE_START_H_

#include <vector>
#include "data/internal/Session.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



namespace Packet {

    namespace Event {

        struct RaceStart : public Packet::Event::Interface {

            public:
            // Packet interface constructor
            RaceStart();

            // Destructor
            virtual ~RaceStart() = default;

            // Type identifier for the packet
            const Packet::Event::Type packetType() const override final;

            // Structure containing the number of minisectors per sector; sector IDs are index - 1
            std::vector<uint8_t> m_sectorConfiguration;

            // Structure containing all relevant data about the session taking place
            Session::Internal::Settings m_settings;

            // List containing the initial data for all session participants
            std::vector<Session::Internal::Participant> m_participants;

        };

    }

}

#endif  //  PACKETS_EVENT_INCLUDE_RACE_START_H_