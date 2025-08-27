#ifndef PACKETS_EVENT_INCLUDE_QUALI_START_H_
#define PACKETS_EVENT_INCLUDE_QUALI_START_H_

#include "data/internal/Session.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



namespace Packet {

    namespace Event {

        struct QualiStart : public Packet::Event::Interface {

            // Packet constructor
            QualiStart(const uint64_t timestamp, uint8_t carsClassifiedAtEnd);

            // Destructor
            virtual ~QualiStart() = default;

            // Type identifier for the packet
            const Packet::Event::Type packetType() const override final;

            // How many cars go through to the next round
            const uint8_t m_carsClassifiedAtEnd;

        };

    }

}

#endif  //  PACKETS_EVENT_INCLUDE_QUALI_START_H_