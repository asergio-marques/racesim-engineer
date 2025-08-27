#ifndef PACKETS_EVENT_INCLUDE_RACE_START_H_
#define PACKETS_EVENT_INCLUDE_RACE_START_H_

#include "data/internal/Session.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



namespace Packet {

    namespace Event {

        struct RaceStart : public Packet::Event::Interface {

            public:
            // Packet interface constructor
            RaceStart(const uint64_t timestamp, uint8_t numLaps);

            // Destructor
            virtual ~RaceStart() = default;

            // Type identifier for the packet
            const Packet::Event::Type packetType() const override final;

            // Number of laps in the race
            const uint8_t m_numLaps;

        };

    }

}

#endif  //  PACKETS_EVENT_INCLUDE_RACE_START_H_