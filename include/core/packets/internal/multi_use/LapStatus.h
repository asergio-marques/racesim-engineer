#ifndef PACKETS_INTERNAL_INCLUDE_LAP_STATUS_H_
#define PACKETS_INTERNAL_INCLUDE_LAP_STATUS_H_

#include <cstdint>
#include <vector>
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



namespace Packet {

    namespace Internal {

        struct LapStatus : public Packet::Internal::Interface {

            struct Data {

                public:
                // Constructor
                Data() = default;

                // ID of the driver for which this lap is relative to
                uint8_t m_driverID;

                // ID of the lap to which this information pertains
                uint8_t m_lapID;

                // Whether is lap is an outlap, inlap or regular lap
                Lap::Internal::Type m_type;

                // Whether the lap has been invalidated (or not) or if it's a simple cooldown lap in between pushlaps
                Lap::Internal::Status m_status;

                // Container for the times for each mini-sector of the track (0 = mini-sector 1, 1 = mini-sector 2...)
                std::vector<Lap::Internal::Time> m_miniSectorTimes;

                // Container for the times for each sector of the track (0 = sector 1, 1 = sector 2...)
                std::vector<Lap::Internal::Time> m_sectorTimes;

                // Track distance the vehicle has travelled in the current lap (meters)
                float_t m_lapDistanceRun;

            };
            public:
            // Packet interface constructor
            LapStatus(const uint64_t timestamp);

            // Destructor
            virtual ~LapStatus() = default;

            // Type identifier for the packet
            const Packet::Internal::Type packetType() const override final;

            // Adds status data into the packet
            void InsertData(const Packet::Internal::LapStatus::Data data);

            // Retrieve status data from the packet
            const std::vector<Packet::Internal::LapStatus::Data>& GetData() const;

            private:
            // Holds the current status of all drivers in the session
            std::vector<Packet::Internal::LapStatus::Data> m_fullStatusData;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_LAP_STATUS_H_