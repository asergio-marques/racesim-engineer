#ifndef PACKETS_EVENT_INCLUDE_PENALTY_RECEIVED_H_
#define PACKETS_EVENT_INCLUDE_PENALTY_RECEIVED_H_

#include <cstdint>
#include "data/internal/Penalty.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"


namespace Packet {

    namespace Event {

        struct PenaltyReceived : public Packet::Event::Interface {

            public:
            // Packet interface constructor
            PenaltyReceived(const bool isPlayer, const std::string fullName, const uint8_t currentPosition);

            // Destructor
            virtual ~PenaltyReceived() = default;

            // Type identifier for the packet
            const Packet::Event::Type packetType() const override final;

            // Index for this participant
            uint8_t m_index;

            // Type of penalty given to the vehicle
            Penalty::Internal::Type m_type;

            // Change to this type of penalty, if time or stop-go,
            // then it is represented in milliseconds
            int32_t m_delta;

        };

    }

}

#endif  //  PACKETS_EVENT_INCLUDE_PENALTY_RECEIVED_H_