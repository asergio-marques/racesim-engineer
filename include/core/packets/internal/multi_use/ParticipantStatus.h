#ifndef PACKETS_INTERNAL_INCLUDE_PARTICIPANT_STATUS_H_
#define PACKETS_INTERNAL_INCLUDE_PARTICIPANT_STATUS_H_

#include <cstdint>
#include <vector>
#include "data/internal/Participant.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"


namespace Packet {

    namespace Internal {

        struct ParticipantStatus : public Packet::Internal::Interface {

            struct Data {

                public:
                // Constructor
                Data(const uint8_t driverID, const Participant::Internal::Status status);

                // ID of the driver for which this status is relative to
                const uint8_t m_driverID;

                // Current status of the driver
                const Participant::Internal::Status m_status;

            };
            public:
            // Packet interface constructor
            ParticipantStatus(const uint64_t timestamp);

            // Destructor
            virtual ~ParticipantStatus() = default;

            // Type identifier for the packet
            const Packet::Internal::Type packetType() const override final;

            // Adds status data into the packet
            void InsertData(const uint8_t driverID, const Participant::Internal::Status status);

            // Retrieve status data from the packet
            const std::vector<Packet::Internal::ParticipantStatus::Data>& GetData() const;

            private:
            // Holds the current status of all drivers in the session
            std::vector<Packet::Internal::ParticipantStatus::Data> m_fullStatusData;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_PARTICIPANT_STATUS_H_