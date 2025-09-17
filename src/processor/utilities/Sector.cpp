#include "utilities/Sector.h"

#include <cstdint>
#include <map>
#include "data/internal/Sector.h"




Lap::Internal::Sector Processor::Utility::Sector::INVALID_SECTOR = Lap::Internal::Sector(0, 0, 0);



bool Processor::Utility::Sector::validate(const Lap::Internal::Sector& sector) {

    return (sector.m_ID == 0 || (sector.m_startPoint == 0 && sector.m_endPoint == 0));

}



Lap::Internal::Sector& Processor::Utility::Sector::getPreviousSectorByDistance(
    std::map<uint8_t, Lap::Internal::Sector>& sectors, const uint32_t distance, bool& usePreviousLap) {

    usePreviousLap = false;

    auto& currentSector = getSectorByDistance(sectors, distance);

    if (!validate(currentSector)) {

        return Processor::Utility::Sector::INVALID_SECTOR;

    }

    // normal case
    auto& previousSector = getSectorById(sectors, currentSector.m_ID - 1);
    if (validate(previousSector)) {

        return previousSector;

    }

    // case in which we are on the first sector - need to get the last sector of the lap
    usePreviousLap = true;
    return Processor::Utility::Sector::INVALID_SECTOR;

}



Lap::Internal::Sector& Processor::Utility::Sector::getSectorByDistance(
    std::map<uint8_t, Lap::Internal::Sector>& sectors, const uint32_t distance) {

    for (auto& sectorEntry : sectors) {

        auto& sector = sectorEntry.second;

        if (distance >= sector.m_startPoint && distance <= sector.m_endPoint) {

            return sector;

        }

    }

    return Processor::Utility::Sector::INVALID_SECTOR;

}



Lap::Internal::Sector& Processor::Utility::Sector::getSectorById(
    std::map<uint8_t, Lap::Internal::Sector>& sectors, const uint8_t id) {

    if (id == 0) return Processor::Utility::Sector::INVALID_SECTOR;

    auto it = sectors.find(id);
    if (it != sectors.end()) return it->second;

    return Processor::Utility::Sector::INVALID_SECTOR;

}



Lap::Internal::Sector& Processor::Utility::Sector::getPreviousMiniSectorByDistance(
    std::map<uint8_t, Lap::Internal::Sector>& sectors, const uint32_t distance, bool& usePreviousLap) {

    usePreviousLap = false;

    auto& currentSector = getSectorByDistance(sectors, distance);
    auto& currentMiniSector = getMiniSectorByDistance(sectors, distance);

    if (!validate(currentSector) || !validate(currentMiniSector)) {

        return Processor::Utility::Sector::INVALID_SECTOR;

    }

    // normal case
    auto& previousMiniSector = getMiniSectorById(sectors, currentSector.m_ID, currentMiniSector.m_ID - 1);
    if (validate(previousMiniSector)) return previousMiniSector;

    // case in which we are on the first minisector of a sector - need to get the last minisector of the previous sector
    auto& previousSector = getSectorById(sectors, currentSector.m_ID - 1);
    if (validate(previousSector)) {
        
        // get the highest ID of the minisectors of the previous lap, that will be the previous minisector
        uint8_t maxId = 0;
        for (auto& miniSector : previousSector.m_minisectors) {

            if (miniSector.second.m_ID > maxId) {

                maxId = miniSector.second.m_ID;

            }

        }

        return getMiniSectorById(sectors, previousSector.m_ID, maxId);

    }
    // case in which we are on the first minisector of the first sector - need to signal that another request to this utils
    // needs to be done, with the previous lap's sectors
    usePreviousLap = true;
    return Processor::Utility::Sector::INVALID_SECTOR;

}



Lap::Internal::Sector& Processor::Utility::Sector::getMiniSectorByDistance(
    std::map<uint8_t, Lap::Internal::Sector>& sectors, const uint32_t distance) {

    for (auto& sectorEntry : sectors) {

        auto& sector = sectorEntry.second;

        if (distance >= sector.m_startPoint && distance <= sector.m_endPoint) {

            for (auto& miniSectorEntry : sector.m_minisectors) {

                auto& miniSector = miniSectorEntry.second;

                if (distance >= miniSector.m_startPoint && distance <= miniSector.m_endPoint) {

                    return miniSector;

                }

            }

        }

    }

    return Processor::Utility::Sector::INVALID_SECTOR;

}



Lap::Internal::Sector& Processor::Utility::Sector::getMiniSectorById(
    std::map<uint8_t, Lap::Internal::Sector>& sectors, const uint8_t sectorId, const uint8_t miniSectorId) {

    if (sectorId == 0 || miniSectorId == 0) return Processor::Utility::Sector::INVALID_SECTOR;

    auto sectorIt = sectors.find(sectorId);
    if (sectorIt != sectors.end()) {

        auto miniSectorIt = sectorIt->second.m_minisectors.find(miniSectorId);
        if (miniSectorIt != sectorIt->second.m_minisectors.end()) {

            return miniSectorIt->second;

        }

    }

    return Processor::Utility::Sector::INVALID_SECTOR;

}