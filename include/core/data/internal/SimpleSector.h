#ifndef DATA_INTERNAL_INCLUDE_SIMPLE_SECTOR_H_
#define DATA_INTERNAL_INCLUDE_SIMPLE_SECTOR_H_

#include <cmath>
#include <cstdint>
#include <vector>
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"




namespace Lap::Internal {

    struct SimpleSector {

        SimpleSector(const uint8_t driverID, const uint16_t lapID, const uint8_t sectorID);

        SimpleSector(const SimpleSector& other);

        SimpleSector& operator=(const SimpleSector& other);

        bool operator==(const SimpleSector& other) const;

        // Retrieves the total run time spent inside this sector
        const Lap::Internal::Time totalTime() const;

        // Retrieves the identifier of the driver who drove this sector
        const uint8_t getDriverID() const;

        // Retrieves the identifier of the lap this sector is part of
        const uint8_t getLapID() const;

        // Retrieves the identifier of this sector in the overall lap
        const uint8_t getSectorID() const;

        // The time the driver has spent running in this sector
        // If m_performance notes that the sector has been finished, then this is the final sector time
        Lap::Internal::Time m_finalLapTime;

        // Notes the current status of this sector
        Lap::Internal::Status m_status;        

        // Notes the performance of the driver in this sector in terms of improvement/pits/retirement
        Lap::Internal::Performance m_performance;

        private:
        // Identifier of the driver who drove this sector/minisector
        uint8_t m_driverID;

        // Identifier of the lap this sector/minisector is part of
        uint8_t m_lapID;

        // Whether this sector is the 1st, 2nd, 3rd... etc
        uint8_t m_sectorID;

    };

}



#endif // DATA_INTERNAL_INCLUDE_SIMPLE_SECTOR_H_