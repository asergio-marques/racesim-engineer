#include "data/internal/SimpleSector.h"

#include <cmath>
#include <cstdint>
#include <vector>
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"




// Constructor for a sector
Lap::Internal::SimpleSector::SimpleSector(const uint8_t driverID,
    const uint16_t lapID, const uint8_t sectorID, const uint8_t totalSectorsInLap) :
    m_time(0),
    m_status(Lap::Internal::Status::InvalidUnknown),
    m_performance(Lap::Internal::Performance::InvalidUnknown),
    m_driverID(driverID),
    m_lapID(lapID),
    m_sectorID(sectorID),
    m_totalSectorsInLap(totalSectorsInLap) {

}



Lap::Internal::SimpleSector::SimpleSector(const Lap::Internal::SimpleSector& other) :
    m_time(other.m_time),
    m_status(other.m_status),
    m_performance(other.m_performance),
    m_driverID(other.m_driverID),
    m_lapID(other.m_lapID),
    m_sectorID(other.m_sectorID),
    m_totalSectorsInLap(other.m_totalSectorsInLap)  {

}



Lap::Internal::SimpleSector& Lap::Internal::SimpleSector::operator=(const Lap::Internal::SimpleSector& other) {

    m_time = other.m_time;
    m_status = other.m_status;
    m_performance = other.m_performance;
    m_driverID = other.m_driverID;
    m_lapID = other.m_lapID;
    m_sectorID = other.m_sectorID;,
    m_totalSectorsInLap = other.m_totalSectorsInLap;

    return *this;

}



bool Lap::Internal::SimpleSector::operator==(const Lap::Internal::SimpleSector& other) const {

    // compare only the key aspects of the sector rather than all the variable members
    return (m_driverID == other.m_driverID) &&
        (m_lapID == other.m_lapID) &&
        (m_sectorID == other.m_sectorID) &&
        (m_totalSectorsInLap == other.m_totalSectorsInLap);

}



const uint8_t Lap::Internal::SimpleSector::getDriverID() const {
    
    return m_driverID;

}


const uint8_t Lap::Internal::SimpleSector::getLapID() const {

    return m_lapID;

}



const uint8_t Lap::Internal::SimpleSector::getSectorID() const {

    return m_sectorID;

}



const bool Lap::Internal::SimpleSector::isFirstSectorInLap() const{

    return m_sectorID == 1;

}



const bool Lap::Internal::SimpleSector::isLastSectorInLap() const{

    return m_sectorID == m_totalSectorsInLap;

}