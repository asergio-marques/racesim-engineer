#ifndef DATA_INTERNAL_INCLUDE_SECTOR_H_
#define DATA_INTERNAL_INCLUDE_SECTOR_H_

#include <cmath>
#include <cstdint>
#include <vector>
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"




namespace Lap::Internal {

    struct Sector {

        // Constructor for a sector
        Sector(const uint8_t driverID, const uint8_t orderID, const uint16_t numPreviousLaps, const size_t numSectorsLap,
            float_t startDistance, float_t endDistance, Lap::Internal::Time initialLapTime);

        // Constructor for a minisector
        Sector(const uint8_t driverID, const uint8_t orderID, const uint16_t numPreviousLaps, const size_t numMiniSectorsLap,
            const uint8_t parentID, const uint8_t sectorOrderID, float_t startDistance, float_t endDistance,
            Lap::Internal::Time initialLapTime);

        // Comparison operator
        bool operator==(const Sector& other) const;

        // Retrieves the total run time spent inside this sector/minisector
        const Lap::Internal::Time totalTime() const;

        // Retrieves the identifier of the driver who drove this sector/minisector
        const uint8_t getDriverID() const;

        // Retrieves the identifier of this sector/minisector in the overall lap
        const uint8_t getLapOrderID() const;

        // Retrieves the identifier of this sector/minisector in the entire race
        const uint16_t getUniqueOverallID() const;

        // Retrieves the identifier of the sector this minisector belongs to
        const uint8_t getParentID() const;

        // Retrieves the identifier of this sector/minisector in the immediately larger container
        const uint8_t getParentOrderID() const;

        // Retrieves the lap distance at which this (mini)sector begins
        const float_t getStartPoint() const;

        // Retrieves the lap distance at which this (mini)sector ends
        const float_t getEndPoint() const;

        // Retrieves whether this object actually represents a mini-sector
        const bool isMiniSector() const;

        // The time the driver has spent running in this (mini)sector
        // If m_performance notes that the sector has been finished, then this is the final sector time
        Lap::Internal::Time m_finalLapTime;

        // Notes the current status of this (mini)sector
        Lap::Internal::Status m_status;        

        // Notes the performance of the driver in this (mini)sector in terms of improvement/pits/retirement
        Lap::Internal::Performance m_performance;

        private:
        // Identifier of the driver who drove this sector/minisector
        uint8_t m_driverID;

        // Identifier of this sector/minisector in the overall lap
        // - If this is a minisector, then it's a unique ID among all minisectors of this lap, in order
        //      (e.g. if sector 1 had 4 minisectors, minisector 2 of sector 2 means m_lapOrderID == 6)
        uint8_t m_lapOrderID;

        // Identifier of this sector/minisector in the entire race
        //      (e.g. if a track has 3 sectors per lap, m_uniqueOverallID == 4 means sector 1 of lap 2)
        //      (e.g. if a track has 20 minisectors per lap, m_uniqueOverallID == 125 means sector 5 of lap 7)
        uint16_t m_uniqueOverallID;

        // Identifier of the lap this sector/minisector is part of
        uint8_t m_lapID;

        // Identifier of the sector this minisector belongs to
        // - If this is a sector, then it's 0
        uint8_t m_parentID;

        // Identifier of this sector/minisector in the immediately larger container
        // - If this is a sector, then it's the same as the m_orderID
        // - If this is a minisector, then it's a unique ID among all minisectors of this sector, in order
        //      (e.g. if sector 1 had 4 minisectors, minisector 2 of sector 2 means m_parentOrderID == 2)
        uint8_t m_parentOrderID;

        // The lap distance at which this (mini)sector begins (meters)
        float_t m_startPoint;

        // The lap distance at which this (mini)sector ends (meters)
        float_t m_endPoint;

        // The lap time the driver was at when first reaching this sector
        Lap::Internal::Time m_initialLapTime;

        // Whether this object actually represents a mini-sector; if so, m_minisectors must be empty
        bool m_isMiniSector;

    };

}



#endif // DATA_INTERNAL_INCLUDE_SECTOR_H_