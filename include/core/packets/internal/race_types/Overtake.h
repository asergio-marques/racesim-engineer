#ifndef PACKETS_INTERNAL_RACE_INCLUDE_OVERTAKE_H_
#define PACKETS_INTERNAL_RACE_INCLUDE_OVERTAKE_H_

#include <cstdint>
#include <vector>
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



namespace Packet {

    namespace Internal {

        struct Overtake : public Packet::Internal::Interface {

            struct Data {

                public:
                // Constructor
                Data(const uint8_t driverID, const uint8_t newPosition, const bool positionUp);

                // ID of the driver whose position has changed
                const uint8_t m_driverID;

                // New position for this driver
                const uint8_t m_position;

                // Whether the driver's overall position went up or down
                const bool m_moveUp;

            };

            public:
            // Packet constructor
            Overtake(const uint64_t timestamp);

            // Destructor
            virtual ~Overtake() = default;

            // Type identifier for the packet
            const Packet::Internal::Type packetType() const override final;

            // Adds overtake data into the packet
            void InsertData(const uint8_t driverID, const uint8_t newPosition, const bool positionUp);

            // Retrieves the overtake data in the packet
            const std::vector<Packet::Internal::Overtake::Data>& GetData() const;

            private:
            // Holds all the data with the drivers involved in an overtake
            std::vector<Packet::Internal::Overtake::Data> m_fullOvertakeData;

        };

    }

}

#endif  //  PACKETS_INTERNAL_RACE_INCLUDE_OVERTAKE_H_