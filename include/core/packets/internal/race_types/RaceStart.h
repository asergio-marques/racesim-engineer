#ifndef PACKETS_INTERNAL_RACE_INCLUDE_RACE_START_H_
#define PACKETS_INTERNAL_RACE_INCLUDE_RACE_START_H_

#include <list>
#include "data/internal/Session.h"
#include "packets/internal/MPSessionStart.h"
#include "packets/internal/Type.h"



namespace Packet {

    namespace Internal {

        struct RaceStart : public Packet::Internal::MPSessionStart {

            public:
            // Packet interface constructor
            RaceStart(const uint64_t timestamp, uint8_t numLaps);

            // Destructor
            virtual ~RaceStart() = default;

            // Number of laps in the race
            const uint8_t m_numLaps;

        };

    }

}

#endif  //  PACKETS_INTERNAL_RACE_INCLUDE_RACE_START_H_