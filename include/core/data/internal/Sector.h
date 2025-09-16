#ifndef DATA_INTERNAL_INCLUDE_SECTOR_H_
#define DATA_INTERNAL_INCLUDE_SECTOR_H_

#include <cmath>
#include <cstdint>
#include <map>
#include <vector>
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"




namespace Lap::Internal {

    struct Sector {

        // Constructor for a minisector
        Sector(const uint8_t id, float_t startDistance, float_t endDistance);

        // Constructor for a sector
        Sector(const uint8_t id, float_t startDistance, float_t endDistance,
            const std::vector<Lap::Internal::Sector>& miniSectors);

        // Alternative constructor for a sector
        Sector(const uint8_t id, float_t startDistance, float_t endDistance,
            const std::map<uint8_t, Lap::Internal::Sector>& miniSectors);

        // Identifier of this sector in the lap/sector (in the case of minisector)
        const uint8_t m_ID;

        // The lap distance at which this (mini)sector begins (meters)
        const float_t m_startPoint;

        // The lap distance at which this (mini)sector ends (meters)
        const float_t m_endPoint;

        // The time the driver has spent running in this (mini)sector
        // If m_performance notes that the sector has been finished, then this is the final sector time
        Lap::Internal::Time m_currentTime;

        // Notes the current status of this (mini)sector
        Lap::Internal::Status m_status;        

        // Notes the performance of the driver in this (mini)sector in terms of improvement/pits/retirement
        Lap::Internal::Performance m_performance;

        // Denotes whether this object actually represents a mini-sector; if so, m_minisectors must be empty
        const bool m_isMiniSector;

        // Array that contains the minisectors that compose this sector (empty if m_isMiniSector is true)
        std::map<uint8_t, Lap::Internal::Sector> m_minisectors;

    };

}



#endif // DATA_INTERNAL_INCLUDE_SECTOR_H_