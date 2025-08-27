#ifndef PACKETS_INTERNAL_RACE_INCLUDE_PENALTY_STATUS_H_
#define PACKETS_INTERNAL_RACE_INCLUDE_PENALTY_STATUS_H_

#include <cstdint>
#include <vector>
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



namespace Packet {

    namespace Internal {

        struct PenaltyStatus : public Packet::Internal::Interface {

            struct Data {

                public:
                // Constructor
                Data(const uint8_t driverID, const uint8_t totalWarnings,
                    const uint8_t trackLimitWarnings, const uint16_t timePenalties,
                    const uint8_t stopGoPens, const uint8_t driveThroughPens);

                // ID of the driver for which this standing is relative to
                const uint8_t m_driverID;

                // Number of warnings of all types issued
                const uint8_t m_totalWarns;

                // Number of outstanding track limit warnings
                const uint8_t m_numTrackLimits;

                // Time penalty (in millisseconds) to be added at the end of the session
                const uint16_t m_timePenMS;

                // Number of stop-go penalties still to be served
                const uint8_t m_numStopGo;

                // Number of drive-through penalties still to be served
                const uint8_t m_numDriveThrough;

            };

            public:
            // Packet constructor
            PenaltyStatus(const uint64_t timestamp);

            // Destructor
            virtual ~PenaltyStatus() = default;

            // Type identifier for the packet
            const Packet::Internal::Type packetType() const override final;

            // Adds penalty data into the packet
            void InsertData(const uint8_t driverID, const uint8_t totalWarnings,
                    const uint8_t trackLimitWarnings, const uint16_t timePenalties,
                    const uint8_t stopGoPens, const uint8_t driveThroughPens);

            // Retrieve penalty data from the packet
            const std::vector<Packet::Internal::PenaltyStatus::Data>& GetData() const;

            private:
            // Holds the current penalty & warning status of all drivers in the session
            std::vector<Packet::Internal::PenaltyStatus::Data> m_fullPenaltyData;

        };

    }

}

#endif  //  PACKETS_INTERNAL_RACE_INCLUDE_PENALTY_STATUS_H_