#include "data/internal/Sector.h"

#include <cmath>
#include <cstdint>
#include <vector>
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"




// Constructor for a sector
Lap::Internal::Sector::Sector(const uint8_t driverID, const uint8_t orderID, const uint16_t numPreviousLaps,
    const size_t numSectorsLap, float_t startDistance, float_t endDistance, Lap::Internal::Time initialLapTime) :
    m_finalLapTime(0),
    m_status(Lap::Internal::Status::InvalidUnknown),
    m_performance(Lap::Internal::Performance::InvalidUnknown),
    m_lapOrderID(orderID),
    m_driverID(driverID),
    m_uniqueOverallID((numPreviousLaps * numSectorsLap) + orderID),
    m_lapID(numPreviousLaps + 1),
    m_parentID(0),
    m_parentOrderID(orderID),
    m_startPoint(startDistance),
    m_endPoint(endDistance),
    m_initialLapTime(initialLapTime),
    m_isFinalSector(m_lapOrderID == numSectorsLap),
    m_isMiniSector(false) {

}



// Constructor for a minisector
Lap::Internal::Sector::Sector(const uint8_t driverID, const uint8_t orderID, const uint16_t numPreviousLaps,
    const size_t numMiniSectorsLap, const uint8_t parentID, const uint8_t sectorOrderID,
    float_t startDistance, float_t endDistance, Lap::Internal::Time initialLapTime) :
    m_finalLapTime(0),
    m_status(Lap::Internal::Status::InvalidUnknown),
    m_performance(Lap::Internal::Performance::InvalidUnknown),
    m_driverID(driverID),
    m_lapOrderID(orderID),
    m_uniqueOverallID((numPreviousLaps * numMiniSectorsLap) + orderID),
    m_lapID(numPreviousLaps + 1),
    m_parentID(parentID),
    m_parentOrderID(sectorOrderID),
    m_startPoint(startDistance),
    m_endPoint(endDistance),
    m_initialLapTime(initialLapTime),
    m_isFinalSector(m_lapOrderID == numMiniSectorsLap),
    m_isMiniSector(true) {



}



Lap::Internal::Sector::Sector(const Lap::Internal::Sector& other) :
    m_finalLapTime(other.m_finalLapTime),
    m_status(other.m_status),
    m_performance(other.m_performance),
    m_driverID(other.m_driverID),
    m_lapOrderID(other.m_lapOrderID),
    m_uniqueOverallID(other.m_uniqueOverallID),
    m_lapID(other.m_lapID),
    m_parentID(other.m_parentID),
    m_parentOrderID(other.m_parentOrderID),
    m_startPoint(other.m_startPoint),
    m_endPoint(other.m_endPoint),
    m_initialLapTime(other.m_initialLapTime),
    m_isFinalSector(other.m_isFinalSector),
    m_isMiniSector(other.m_isMiniSector) {

}



Lap::Internal::Sector& Lap::Internal::Sector::operator=(const Lap::Internal::Sector& other) {

    m_finalLapTime = other.m_finalLapTime;
    m_status = other.m_status;
    m_performance = other.m_performance;
    m_driverID = other.m_driverID;
    m_lapOrderID = other.m_lapOrderID;
    m_uniqueOverallID = other.m_uniqueOverallID;
    m_lapID = other.m_lapID;
    m_parentID = other.m_parentID;
    m_parentOrderID = other.m_parentOrderID;
    m_startPoint = other.m_startPoint;
    m_endPoint = other.m_endPoint;
    m_initialLapTime = other.m_initialLapTime;
    m_isFinalSector = other.m_isFinalSector;
    m_isMiniSector = other.m_isMiniSector;

    return *this;

}



bool Lap::Internal::Sector::operator==(const Lap::Internal::Sector& other) const {

    // compare only the key aspects of the sector rather than all the variable members
    return (m_lapOrderID == other.m_lapOrderID) &&
        (m_lapID == other.m_lapID) &&
        (m_parentID == other.m_parentID) &&
        (m_parentOrderID == other.m_parentOrderID) &&
        (m_startPoint == other.m_startPoint) &&
        (m_endPoint == other.m_endPoint) &&
        (m_isFinalSector == other.m_isFinalSector) &&
        (m_isMiniSector == other.m_isMiniSector);

}



const Lap::Internal::Time Lap::Internal::Sector::totalTime() const {

    auto temp = m_finalLapTime;
    return temp - m_initialLapTime;

}



const uint8_t Lap::Internal::Sector::getDriverID() const {
    
    return m_driverID;

}



const uint8_t Lap::Internal::Sector::getLapOrderID() const {

    return m_lapOrderID;

}



const uint16_t Lap::Internal::Sector::getUniqueOverallID() const {

    return m_uniqueOverallID;

}


const uint8_t Lap::Internal::Sector::getLapID() const {

    return m_lapID;

}



const uint8_t Lap::Internal::Sector::getParentID() const {

    return m_parentID;

}



const uint8_t Lap::Internal::Sector::getParentOrderID() const {

    return m_parentOrderID;

}



const float_t Lap::Internal::Sector::getStartPoint() const {

    return m_startPoint;

}



const float_t Lap::Internal::Sector::getEndPoint() const {

    return m_endPoint;

}



const bool Lap::Internal::Sector::isFinalSector() const {

    return m_isFinalSector;

}



const bool Lap::Internal::Sector::isMiniSector() const {

    return m_isMiniSector;

}
