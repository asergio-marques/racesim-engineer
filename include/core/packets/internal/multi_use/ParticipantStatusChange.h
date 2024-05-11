#ifndef PACKETS_INTERNAL_INCLUDE_PARTICIPANT_STATUS_CHANGE_H_
#define PACKETS_INTERNAL_INCLUDE_PARTICIPANT_STATUS_CHANGE_H_

#include <cstdint>
#include "data/internal/Participant.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"


namespace Packet {

    namespace Internal {

        struct ParticipantStatusChange : public Packet::Internal::Interface {

            public:
            // Packet interface constructor
            ParticipantStatusChange(const uint64_t timestamp);

            // Destructor
            virtual ~ParticipantStatusChange() = default;

            // Type identifier for the packet
            const Packet::Internal::Type packetType() const override final;

            // Index for this participant
            uint8_t m_index;

            // Status for this vehicle
            Participant::Internal::Status m_status;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_PARTICIPANT_STATUS_CHANGE_H_