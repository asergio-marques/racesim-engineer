#include "data/holders/SectorHistoryData.h"

#include <cstdint>
#include <vector>
#include <map>
#include "data/internal/Lap.h"
#include "data/internal/Sector.h"
#include "data/holders/TrackData.h"
#include "utilities/Sector.h"




Processor::Data::SectorHistoryData::SectorHistoryData(const bool isMinisector,
    const Processor::Data::TrackData& trackDataReference) :
    m_sectors(),
    m_personalBestSectorMap(),
    m_trackDataReference(trackDataReference),
    m_minisector(isMinisector),
    m_isDataComplete(false) {

    // Build PB map based on trackdata
    // Default PB lap is 0 for sectors and minisectors both
    if (isMinisector) {

        const auto& ms = trackDataReference.copyMiniSectors();
        for (const auto& minisector : ms) {

            m_personalBestSectorMap.emplace(minisector.getLapOrderID(), 0);

        }

    }
    else {

        const auto& s = trackDataReference.copySectors();
        for (const auto& sector : s) {

            m_personalBestSectorMap.emplace(sector.getLapOrderID(), 0);

        }

    }

}



bool Processor::Data::SectorHistoryData::installDetector(Processor::Detector::Interface* detector) {

    return true;

}



const bool Processor::Data::SectorHistoryData::Initialized() const {

    return !m_personalBestSectorMap.empty();

}



const bool Processor::Data::SectorHistoryData::Finalized() const {

    return m_isDataComplete;

}



void Processor::Data::SectorHistoryData::initialize() {

    // TODO

}



void Processor::Data::SectorHistoryData::completeData() {

    // TODO

}



void Processor::Data::SectorHistoryData::update(const uint8_t id, const float_t lapDistanceRun,
    const Lap::Internal::Time currentLapTime, const Lap::Internal::Time previousLapTime, const Lap::Internal::Status status) {

    // function is only meant to be used for minisectors
    if (!m_minisector) return;
    bool createNew = m_sectors.empty();

    auto& currentSector = m_sectors.rbegin()->second;
    auto& previousSector = currentSector;
    if (m_sectors.size() > 1) {

        previousSector = std::prev(m_sectors.rbegin())->second;

    }
    updateSector(previousSector, currentSector, currentLapTime, status);
    if (lapDistanceRun >= currentSector.getEndPoint()) {

        // TODO what do when sector finished, aside from creating a new one
        createNew = true;

    }
    if (createNew) {

        // Initialize new sectors, and add them to the overall map and to the lap data
        auto sectors = m_trackDataReference.copySectors();
        auto minisectors = m_trackDataReference.copyMiniSectors();
        const uint16_t lapID = std::floor(m_sectors.size() / minisectors.size()) + 1;

        const auto& currentSectorTemplate = Processor::Utility::Sector::getSectorByDistance(sectors, lapDistanceRun);
        const auto& currentMinisectorTemplate = Processor::Utility::Sector::getSectorByDistance(minisectors, lapDistanceRun);

        Lap::Internal::Sector newMinisector{ currentMinisectorTemplate.getLapOrderID(),
            static_cast<uint16_t>(lapID - 1),
            minisectors.size(),
            currentSectorTemplate.getLapOrderID(),
            currentMinisectorTemplate.getParentOrderID(),
            currentMinisectorTemplate.getStartPoint(),
            currentMinisectorTemplate.getEndPoint(),
            currentLapTime };

        initializeSector(newMinisector, currentLapTime, status);
        m_sectors.emplace(newMinisector.getUniqueOverallID(), newMinisector);

    }

}



void Processor::Data::SectorHistoryData::update(const uint8_t id, const float_t lapDistanceRun,
    const std::vector<Lap::Internal::Time>& sectorTimes, const Lap::Internal::Time previousLapTime,
    const Lap::Internal::Status status) {

    // function is only meant to be used for sectors
    if (m_minisector || sectorTimes.empty()) return;

    bool createNew = m_sectors.empty();

    auto& currentSector = m_sectors.rbegin()->second;
    auto& previousSector = currentSector;
    if (m_sectors.size() > 1) {

        previousSector = std::prev(m_sectors.rbegin())->second;

    }
    // TODO figure out what to do here with the sector times
    // updateSector(previousSector, currentSector, currentLapTime, status);
    if (lapDistanceRun >= currentSector.getEndPoint()) {

        // TODO what do when sector finished, aside from creating a new one
        createNew = true;

    }
    if (createNew) {

        // Initialize new sectors, and add them to the overall map and to the lap data
        auto sectors = m_trackDataReference.copySectors();
        const uint16_t lapID = std::floor(m_sectors.size() / sectors.size()) + 1;

        const auto& currentSectorTemplate = Processor::Utility::Sector::getSectorByDistance(sectors, lapDistanceRun);

        Lap::Internal::Sector newSector{ currentSectorTemplate.getLapOrderID(),
            static_cast<uint16_t>(lapID - 1),
            sectors.size(),
            currentSectorTemplate.getStartPoint(),
            currentSectorTemplate.getEndPoint(),
            sectorTimes[0]};

        initializeSector(newSector, sectorTimes[0], status);
        m_sectors.emplace(newSector.getUniqueOverallID(), newSector);

    }



}



void Processor::Data::SectorHistoryData::initializeSector(Lap::Internal::Sector& sector,
    const Lap::Internal::Time currentLapTime, const Lap::Internal::Status lapStatus) {

    // Validate the sector first, and verify if it hasn't been inited yet
    if (!Processor::Utility::Sector::validate(sector) || sector.m_finalLapTime != 0) return;

    sector.m_finalLapTime = currentLapTime;
    // Only "flying lap" (interpreted as on-track) and "in pits" are expected inputs
    // the other status/performance levels are derived off of that
    switch (lapStatus) {
        case Lap::Internal::Status::FlyingLap:
            sector.m_status = lapStatus;
            sector.m_performance = Lap::Internal::Performance::CurrentlyRunning;
            break;

        case Lap::Internal::Status::InPits:
            sector.m_status = lapStatus;
            sector.m_performance = Lap::Internal::Performance::CurrentlyRunningPits;
            break;

        default:
            sector.m_status = Lap::Internal::Status::InvalidUnknown;
            sector.m_performance = Lap::Internal::Performance::InvalidUnknown;

    }

}



void Processor::Data::SectorHistoryData::updateSector(Lap::Internal::Sector& previousSector, Lap::Internal::Sector& currentSector,
    const Lap::Internal::Time currentLapTime, const Lap::Internal::Status lapStatus) {

    // check if previous sector is the same as the current sector;
    // this will make the first sector and minisector easier to handle
    if (previousSector == currentSector) {

        // TODO
        return;
    }

    // if we actually have a good previous sector, let's use it as a basis for other stuff shall we

    currentSector.m_finalLapTime = currentLapTime;
    // Only "flying lap" (interpreted as on-track) and "in pits" are expected inputs
    // the status may depend on the previous sector, hence why we need it here as well
    switch (lapStatus) {
        case Lap::Internal::Status::FlyingLap:
            break;

        case Lap::Internal::Status::InPits:
            break;

        default:
            currentSector.m_status = Lap::Internal::Status::InvalidUnknown;
            currentSector.m_performance = Lap::Internal::Performance::InvalidUnknown;

    }

}