#ifndef PACKETS_INTERNAL_INCLUDE_PENALTY_GIVEN_H_
#define PACKETS_INTERNAL_INCLUDE_PENALTY_GIVEN_H_

#include <cstdint>
#include "data/internal/Penalty.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"


namespace Packet {

    namespace Internal {

        struct PenaltyChange : public Packet::Internal::Interface {

            public:
            // Packet interface constructor
            PenaltyChange(const uint64_t timestamp);

            // Destructor
            virtual ~PenaltyChange() = default;

            // Type identifier for the packet
            const Packet::Internal::Type packetType() const override final;

            // Index for this participant
            uint8_t m_index;

            // Type of penalty given to the vehicle
            Penalty::Internal::Type m_type;

            // Change to this type of penalty, if time,
            // then it is represented in milliseconds
            int32_t m_delta;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_PENALTY_GIVEN_H_