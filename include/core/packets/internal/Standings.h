#ifndef PACKETS_INTERNAL_INCLUDE_STANDINGS_H_
#define PACKETS_INTERNAL_INCLUDE_STANDINGS_H_

#include <cstdint>
#include <vector>
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



namespace Packet {

    namespace Internal {

        struct Standings : public Packet::Internal::Interface {

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
            Standings(const uint64_t timestamp);

            // Destructor
            virtual ~Standings() = default;

            // Type identifier for the packet
            const Packet::Internal::Type packetType() const override final;

            // Adds standings data into the packet
            void InsertData(const uint8_t driverID, const uint8_t position);

            // Retrieve standings data from the packet
            const std::vector<Packet::Internal::Standings::Data>& GetData() const;

            private:
            // Holds the current position of all drivers in the session
            std::vector<Packet::Internal::Standings::Data> m_fullStandingsData;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_STANDINGS_H_