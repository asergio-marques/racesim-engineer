#ifndef PACKETS_EVENT_INCLUDE_PARTICIPANT_STATUS_CHANGED_H_
#define PACKETS_EVENT_INCLUDE_PARTICIPANT_STATUS_CHANGED_H_

#include <cstdint>
#include "data/internal/Participant.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"


namespace Packet {

    namespace Event {

        struct ParticipantStatusChanged : public Packet::Event::Interface {

            public:
            // Packet interface constructor
            ParticipantStatusChanged();

            // Destructor
            virtual ~ParticipantStatusChanged() = default;

            // Type identifier for the packet
            const Packet::Event::Type packetType() const override final;

            // Index for this participant
            uint8_t m_index;

            // Status for this vehicle
            Participant::Internal::Status m_status;

        };

    }

}

#endif  //  PACKETS_EVENT_INCLUDE_PARTICIPANT_STATUS_CHANGED_H_