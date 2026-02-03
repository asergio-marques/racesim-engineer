#include "data/internal/SimpleSector.h"

#include <cmath>
#include <cstdint>
#include <vector>
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"




// Constructor for a sector
Lap::Internal::SimpleSector::SimpleSector(const uint8_t driverID,
    const uint16_t lapID, const uint8_t sectorID) :
    m_finalLapTime(0),
    m_status(Lap::Internal::Status::InvalidUnknown),
    m_performance(Lap::Internal::Performance::InvalidUnknown),
    m_driverID(driverID),
    m_lapID(lapID),
    m_sectorID(sectorID) {

}



Lap::Internal::SimpleSector::SimpleSector(const Lap::Internal::SimpleSector& other) :
    m_finalLapTime(other.m_finalLapTime),
    m_status(other.m_status),
    m_performance(other.m_performance),
    m_driverID(other.m_driverID),
    m_lapID(other.m_lapID),
    m_sectorID(other.m_sectorID)  {

}



Lap::Internal::SimpleSector& Lap::Internal::SimpleSector::operator=(const Lap::Internal::SimpleSector& other) {

    m_finalLapTime = other.m_finalLapTime;
    m_status = other.m_status;
    m_performance = other.m_performance;
    m_driverID = other.m_driverID;
    m_lapID = other.m_lapID;
    m_sectorID = other.m_sectorID;

    return *this;

}



bool Lap::Internal::SimpleSector::operator==(const Lap::Internal::SimpleSector& other) const {

    // compare only the key aspects of the sector rather than all the variable members
    return (m_driverID == other.m_driverID) &&
        (m_lapID == other.m_lapID) &&
        (m_sectorID == other.m_sectorID);

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