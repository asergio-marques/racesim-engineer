#include "data/internal/Sector.h"

#include <cstdint>
#include <vector>
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"




Lap::Internal::Sector::Sector(const uint8_t id, float_t startDistance, float_t endDistance) :
    m_ID(id),
    m_startPoint(startDistance),
    m_endPoint(endDistance),
    m_currentTime(0),
    m_status(Lap::Internal::Status::InvalidUnknown),
    m_performance(Lap::Internal::Performance::InvalidUnknown),
    m_isMiniSector(true),
    m_minisectors() {



}



Lap::Internal::Sector::Sector(const uint8_t id, float_t startDistance, float_t endDistance,
    const std::vector<Lap::Internal::Sector>& miniSectors) :
    m_ID(id),
    m_startPoint(startDistance),
    m_endPoint(endDistance),
    m_currentTime(0),
    m_status(Lap::Internal::Status::InvalidUnknown),
    m_performance(Lap::Internal::Performance::InvalidUnknown),
    m_isMiniSector(false),
    m_minisectors() {

    for (const auto& miniSector : miniSectors) {

        m_minisectors.emplace(miniSector.m_ID, miniSector);

    }

}




Lap::Internal::Sector::Sector(const uint8_t id, float_t startDistance, float_t endDistance,
    const std::map<uint8_t, Lap::Internal::Sector>& miniSectors) :
    m_ID(id),
    m_startPoint(startDistance),
    m_endPoint(endDistance),
    m_currentTime(0),
    m_status(Lap::Internal::Status::InvalidUnknown),
    m_performance(Lap::Internal::Performance::InvalidUnknown),
    m_isMiniSector(false),
    m_minisectors(miniSectors) {

}