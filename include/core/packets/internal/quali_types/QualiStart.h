#ifndef PACKETS_INTERNAL_RACE_INCLUDE_QUALI_START_H_
#define PACKETS_INTERNAL_RACE_INCLUDE_QUALI_START_H_

#include <list>
#include "data/internal/Session.h"
#include "packets/internal/multi_use/MPSessionStart.h"
#include "packets/internal/Type.h"



namespace Packet {

    namespace Internal {

        struct QualiStart : public Packet::Internal::MPSessionStart {

            // Packet constructor
            QualiStart(const uint64_t timestamp, uint8_t carsClassifiedAtEnd);

            // Destructor
            virtual ~QualiStart() = default;

            // How many cars go through to the next round
            const uint8_t m_carsClassifiedAtEnd;

        };

    }

}

#endif  //  PACKETS_INTERNAL_RACE_INCLUDE_QUALI_START_H_