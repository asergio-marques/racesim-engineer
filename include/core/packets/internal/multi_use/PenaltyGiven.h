#ifndef PACKETS_INTERNAL_INCLUDE_PENALTY_GIVEN_H_
#define PACKETS_INTERNAL_INCLUDE_PENALTY_GIVEN_H_

#include <cstdint>
#include "data/internal/Penalty.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"


namespace Packet {

    namespace Internal {

        struct PenaltyGiven : public Packet::Internal::Interface {

            public:
            // Packet interface constructor
            PenaltyGiven(const uint64_t timestamp);

            // Destructor
            virtual ~PenaltyGiven() = default;

            // Type identifier for the packet
            const Packet::Internal::Type packetType() const override final;

            // Index for this participant
            uint8_t m_index;

            // Type of penalty given to the vehicle
            Penalty::Internal::Type m_type;

            // Reason for the penalty being given
            Penalty::Internal::Reason m_reasonforPenalty;

            // Number of millisseconds added to vehicle's time,
            // if the penalty is a time penalty
            uint16_t m_timeLength;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_PENALTY_GIVEN_H_