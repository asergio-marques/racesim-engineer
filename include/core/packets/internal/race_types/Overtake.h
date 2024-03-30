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

            const Packet::Internal::Type packetType() const override final;
            void InsertData(const uint8_t driverID, const uint8_t newPosition, const bool positionUp);
            const std::vector<Packet::Internal::Overtake::Data>& GetData() const;

            private:
            std::vector<Packet::Internal::Overtake::Data> m_fullOvertakeData;

        };

    }

}

#endif  //  PACKETS_INTERNAL_RACE_INCLUDE_OVERTAKE_H_