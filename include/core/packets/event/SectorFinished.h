#ifndef PACKETS_EVENT_INCLUDE_SECTOR_FINISHED_H_
#define PACKETS_EVENT_INCLUDE_SECTOR_FINISHED_H_

#include <cstdint>
#include <string>
#include "data/internal/LapTime.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"




namespace Packet {

    namespace Event {

        struct SectorFinished : public Packet::Event::Interface {

            public:
            // Packet interface constructor
            SectorFinished(const bool isPlayer, const std::string fullName, const uint8_t currentPosition);

            // Destructor
            virtual ~SectorFinished() = default;

            // Type identifier for the packet
            const Packet::Event::Type packetType() const override final;

            // Index for this participant
            uint8_t m_index;

            // Time for this newly-finished sector
            Lap::Internal::Time m_lapTime;

        };

    }

}

#endif  //  PACKETS_EVENT_INCLUDE_SECTOR_FINISHED_H_