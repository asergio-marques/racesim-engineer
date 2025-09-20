#ifndef PACKETS_EVENT_INCLUDE_SECTOR_STATE_CHANGED_H_
#define PACKETS_EVENT_INCLUDE_SECTOR_STATE_CHANGED_H_

#include <cstdint>
#include <string>
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"




namespace Packet {

    namespace Event {

        struct SectorStateChanged : public Packet::Event::Interface {

            public:
            // Packet interface constructor
            SectorStateChanged(const bool isPlayer, const std::string fullName, const uint8_t currentPosition);

            // Destructor
            virtual ~SectorStateChanged() = default;

            // Type identifier for the packet
            const Packet::Event::Type packetType() const override final;

            // Index for the participant which finished this sector
            uint8_t m_index;

            // Identifier of the lap to which this sector/minisector belongs to
            uint8_t m_lapID;

            // Identifier of the sector this minisector belongs to (see Lap::Internal::Sector class)
            uint8_t m_parentID;

            // Identifier of this sector/minisector in the immediately larger container (see Lap::Internal::Sector class)
            uint8_t m_sectorParentOrderID;

            // Whether this object actually represents a mini-sector
            bool m_isMiniSector;

            // Notes the status of this (mini)sector when it was finished
            Lap::Internal::Status m_sectorStatus;

            // Notes the performance of the driver in this (mini)sector when it was finished
            Lap::Internal::Performance m_sectorPerformance;

            // Time for this newly-finished sector
            Lap::Internal::Time m_time;

        };

    }

}

#endif  //  PACKETS_EVENT_INCLUDE_SECTOR_STATE_CHANGED_H_