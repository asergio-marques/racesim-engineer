#include "data/internal/Sector.h"

#include <cstdint>
#include <vector>
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"
#include "data/internal/Minisector.h"




Lap::Internal::Sector::Sector(const uint8_t id, uint32_t startDistance, uint32_t endDistance) :
    m_ID(id),
    m_startPoint(startDistance),
    m_endPoint(endDistance),
    m_distanceRan(0),
    m_currentTime(0),
    m_status(0),
    m_performance(0),
    m_isMiniSector(true),
    m_minisectors() {



}



Lap::Internal::Sector::Sector(const uint8_t id, uint32_t startDistance, uint32_t endDistance,
    const std::vector<Lap::Internal::Sector>& miniSectors) :
    m_ID(id),
    m_startPoint(startDistance),
    m_endPoint(endDistance),
    m_distanceRan(0),
    m_currentTime(0),
    m_status(0),
    m_performance(0),
    m_isMiniSector(false),
    m_minisectors(miniSectors) {



}