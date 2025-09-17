#include "data/internal/Sector.h"

#include <cmath>
#include <cstdint>
#include <vector>
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"




Lap::Internal::Sector::Sector(const uint8_t orderID, const uint16_t numPreviousLaps,
    const size_t numSectorsLap, float_t startDistance, float_t endDistance) :
    m_lapOrderID(orderID),
    m_parentOrderID(orderID),
    m_uniqueOverallID((numPreviousLaps * numSectorsLap) + orderID),
    m_startPoint(startDistance),
    m_endPoint(endDistance),
    m_currentTime(0),
    m_status(Lap::Internal::Status::InvalidUnknown),
    m_performance(Lap::Internal::Performance::InvalidUnknown),
    m_isMiniSector(false) {

}



Lap::Internal::Sector::Sector(const uint8_t orderID, const uint16_t numPreviousLaps, const size_t numMiniSectorsLap,
            const uint8_t sectorOrderID, float_t startDistance, float_t endDistance) :
    m_lapOrderID(orderID),
    m_parentOrderID(sectorOrderID),
    m_uniqueOverallID((numPreviousLaps * numMiniSectorsLap) + orderID),
    m_startPoint(startDistance),
    m_endPoint(endDistance),
    m_currentTime(0),
    m_status(Lap::Internal::Status::InvalidUnknown),
    m_performance(Lap::Internal::Performance::InvalidUnknown),
    m_isMiniSector(true) {



}



const uint8_t Lap::Internal::Sector::getLapOrderID() const {

    return m_lapOrderID;

}



const uint8_t Lap::Internal::Sector::getParentOrderID() const {

    return m_parentOrderID;

}



const uint16_t Lap::Internal::Sector::getUniqueOverallID() const {

    return m_uniqueOverallID;

}



const float_t Lap::Internal::Sector::getStartPoint() const {

    return m_startPoint;

}



const float_t Lap::Internal::Sector::getEndPoint() const {

    return m_endPoint;

}


