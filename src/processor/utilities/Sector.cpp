#include "utilities/Sector.h"

#include <cstdint>
#include <map>
#include "data/internal/Sector.h"




Lap::Internal::Sector Processor::Utility::Sector::INVALID_SECTOR = Lap::Internal::Sector(0, 0, 0);



bool Processor::Utility::Sector::validate(const Lap::Internal::Sector& sector) {

    return (sector.m_ID == 0 || (sector.m_startPoint == 0 && sector.m_endPoint == 0));

}



Lap::Internal::Sector& Processor::Utility::Sector::getSectorByDistance(
    std::map<uint8_t, Lap::Internal::Sector>& sectors, const uint32_t distance) {

    return Processor::Utility::Sector::INVALID_SECTOR;

}



Lap::Internal::Sector& Processor::Utility::Sector::getSectorById(
    std::map<uint8_t, Lap::Internal::Sector>& sectors, const uint8_t id) {

    auto it = sectors.find(id);
    if (it != sectors.end()) return it->second;

    return Processor::Utility::Sector::INVALID_SECTOR;

}



Lap::Internal::Sector& Processor::Utility::Sector::getMiniSectorByDistance(
    std::map<uint8_t, Lap::Internal::Sector>& sectors, const uint32_t distance) {

    return Processor::Utility::Sector::INVALID_SECTOR;

}



Lap::Internal::Sector& Processor::Utility::Sector::getMiniSectorById(
    std::map<uint8_t, Lap::Internal::Sector>& sectors, const uint8_t sectorId, const uint8_t miniSectorId) {

    auto sectorIt = sectors.find(sectorId);
    if (sectorIt != sectors.end()) {

        auto miniSectorIt = sectorIt->second.m_minisectors.find(miniSectorId);
        if (miniSectorIt != sectorIt->second.m_minisectors.end()) {

            return miniSectorIt->second;

        }

    }

    return Processor::Utility::Sector::INVALID_SECTOR;

}