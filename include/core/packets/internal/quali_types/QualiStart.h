#ifndef PACKETS_INTERNAL_RACE_INCLUDE_QUALI_START_H_
#define PACKETS_INTERNAL_RACE_INCLUDE_QUALI_START_H_

#include <list>
#include "packets/internal/MPSessionStart.h"
#include "data/internal/Session.h"



namespace Packet {

    namespace Internal {

        struct QualiStart : public Packet::Internal::MPSessionStart {

            // Packet interface constructor
            QualiStart(uint8_t carsClassifiedAtEnd);

            // Destructor
            virtual ~QualiStart() = default;

            // How many cars go through to the next round
            uint8_t m_carsClassifiedAtEnd;

        };

    }

}

#endif  //  PACKETS_INTERNAL_RACE_INCLUDE_QUALI_START_H_