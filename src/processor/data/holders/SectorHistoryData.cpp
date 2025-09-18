#include "data/holders/SectorHistoryData.h"

#include <cstdint>
#include <vector>
#include <map>
#include "data/internal/Lap.h"
#include "data/internal/Sector.h"
#include "data/holders/TrackData.h"
#include "detectors/SectorFinished.h"
#include "detectors/SectorStateChanged.h"
#include "utilities/Sector.h"




Processor::Data::SectorHistoryData::SectorHistoryData(const bool isMinisector,
    const Processor::Data::TrackData& trackDataReference) :
    m_sectors(),
    m_personalBestSectorMap(),
    m_trackDataReference(trackDataReference),
    m_minisector(isMinisector),
    m_isDataComplete(false),
    m_installedFinishedSectorDetector(nullptr),
    m_installedSectorStateChangedDetector(nullptr) {

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

    if (!detector) return false;

    switch (detector->GetType()) {

        case Processor::Detector::Type::SectorFinished:
            m_installedFinishedSectorDetector = dynamic_cast<Processor::Detector::SectorFinished*>(detector);
            return true;

        case Processor::Detector::Type::SectorStateChanged:
            m_installedSectorStateChangedDetector = dynamic_cast<Processor::Detector::SectorStateChanged*>(detector);
            return true;

        default:
            // do nothing
            return false;

    }

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
    const Lap::Internal::Time currentLapTime, const Lap::Internal::Time previousLapTime, const Lap::Internal::Status status, const bool isValid) {

    // function is only meant to be used for minisectors
    if (!m_minisector) return;
    bool createNew = m_sectors.empty();

    auto& currentSector = m_sectors.rbegin()->second;
    auto& previousSector = currentSector;
    if (m_sectors.size() > 1) {

        previousSector = std::prev(m_sectors.rbegin())->second;

    }

    //updateSector(previousSector, currentSector, currentLapTime, status);
    currentSector.m_finalLapTime = currentLapTime;
    // TODO, I need to map this out...
    // the relevant variables are:
    // - Packet::Internal::LapStatus::Data::m_valid - true or false
    // - Packet::Internal::LapStatus::Data::m_status - FlyingLap or InPits
    // - How to reliably determine cooldown, though?
    if ((currentSector.m_status == Lap::Internal::Status::FlyingLap) &&
        (status == Lap::Internal::Status::FlyingLap) &&
        isValid) {

        // no change

    }
    // If the current sector is marked as flying, pits has priority
    else if ((currentSector.m_status == Lap::Internal::Status::FlyingLap) &&
        (status == Lap::Internal::Status::FlyingLap) &&
        !isValid) {

        currentSector.m_status = Lap::Internal::Status::FlyingLapInvalid;
        currentSector.m_performance = Lap::Internal::Performance::CurrentlyRunningInvalid;
        // TODO implement detector to send event packet
        // m_installedSectorStateChanged->AddSectorChange(id, currentSector, m_minisector);

    }
    // If the current sector is marked as flying or flying invalid, pits has priority
    else if (((currentSector.m_status == Lap::Internal::Status::FlyingLap) ||
        (currentSector.m_status == Lap::Internal::Status::FlyingLapInvalid)) &&
        (status == Lap::Internal::Status::InPits)) {

        currentSector.m_status = Lap::Internal::Status::InPits;
        currentSector.m_performance = Lap::Internal::Performance::CurrentlyRunningPits;
        // TODO implement detector to send event packet
        // m_installedSectorStateChanged->AddSectorChange(id, currentSector, m_minisector);

    }

    if (lapDistanceRun >= currentSector.getEndPoint()) {

        // TODO what do when sector finished, aside from creating a new one
        switch (currentSector.m_performance) {

            case Lap::Internal::Performance::CurrentlyRunning:
                currentSector.m_performance = Lap::Internal::Performance::FinishedNormal;
                break;
            case Lap::Internal::Performance::CurrentlyRunningPits:
                currentSector.m_performance = Lap::Internal::Performance::FinishedPits;
                break;
            case Lap::Internal::Performance::CurrentlyRunningInvalid:
                currentSector.m_performance = Lap::Internal::Performance::FinishedInvalid;
                break;

            default:
                // do nothing, these are the only expected statuses if we've just finished this sector
                break;

        }
        evaluateFinishedSector(currentSector);
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
    const Lap::Internal::Status status, const bool isValid) {

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



void Processor::Data::SectorHistoryData::evaluateFinishedSector(const Lap::Internal::Sector& finishedSector) {

    // TODO implement detector to send event packet
    if (!m_installedFinishedSectorDetector || finishedSector.getUniqueOverallID() == 0) return;



}