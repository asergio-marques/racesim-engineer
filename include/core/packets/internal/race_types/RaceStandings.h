#ifndef PACKETS_INTERNAL_RACE_INCLUDE_RACE_STANDINGS_H_
#define PACKETS_INTERNAL_RACE_INCLUDE_RACE_STANDINGS_H_

#include <cstdint>
#include <vector>
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



namespace Packet {

    namespace Internal {

        struct RaceStandings : public Packet::Internal::Interface {

            struct Data {

                public:
                Data(const uint8_t driverID, const uint8_t position);

                // ID of the driver for which this standing is relative to
                const uint8_t m_driverID;

                // Position of this driver in the race
                const uint8_t m_position;

            };

            public:
            // Packet constructor
            RaceStandings(const uint64_t timestamp);

            // Destructor
            virtual ~RaceStandings() = default;

            const Packet::Internal::Type packetType() const override final;
            void Finalize();
            void InsertData(const uint8_t driverID, const uint8_t position);
            const std::vector<Packet::Internal::RaceStandings::Data>& GetData() const;

            private:
            // Number of laps in the race
            bool m_isFinalized;

            std::vector<Packet::Internal::RaceStandings::Data> m_fullStandingsData;

        };

    }

}

#endif  //  PACKETS_INTERNAL_RACE_INCLUDE_RACE_STANDINGS_H_