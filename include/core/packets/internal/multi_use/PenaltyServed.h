#ifndef PACKETS_INTERNAL_INCLUDE_PENALTY_SERVED_H_
#define PACKETS_INTERNAL_INCLUDE_PENALTY_SERVED_H_

#include <cstdint>
#include "data/internal/Penalty.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"


namespace Packet {

    namespace Internal {

        struct PenaltyServed : public Packet::Internal::Interface {

            public:
            // Packet interface constructor
            PenaltyServed(const uint64_t timestamp);

            // Destructor
            virtual ~PenaltyServed() = default;

            // Type identifier for the packet
            const Packet::Internal::Type packetType() const override final;

            // Index for this participant
            uint8_t m_index;

            // Type of penalty that was served
            Penalty::Internal::Type m_type;

            // Number of millisseconds removed from vehicle's penalties,
            // if the penalty served was a time penalty
            uint16_t m_timeLength;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_PENALTY_SERVED_H_