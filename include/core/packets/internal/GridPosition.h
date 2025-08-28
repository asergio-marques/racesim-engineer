#ifndef PACKETS_INTERNAL_INCLUDE_GRID_POSITION_H_
#define PACKETS_INTERNAL_INCLUDE_GRID_POSITION_H_

#include <cstdint>
#include <vector>
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



namespace Packet {

    namespace Internal {

        struct GridPosition : public Packet::Internal::Interface {

            struct Data {

                public:
                // Constructor
                Data(const uint8_t driverID, const uint8_t position);

                // ID of the driver for which this standing is relative to
                const uint8_t m_driverID;

                // Position of this driver in the race
                const uint8_t m_position;

            };

            public:
            // Packet constructor
            GridPosition(const uint64_t timestamp);

            // Destructor
            virtual ~GridPosition() = default;

            // Type identifier for the packet
            const Packet::Internal::Type packetType() const override final;

            // Adds grid position data into the packet
            void InsertData(const uint8_t driverID, const uint8_t position);

            // Retrieve grid position data from the packet
            const std::vector<Packet::Internal::GridPosition::Data>& GetData() const;

            private:
            // Holds the grid position of all drivers in the session
            std::vector<Packet::Internal::GridPosition::Data> m_fullGridData;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_GRID_POSITION_H_