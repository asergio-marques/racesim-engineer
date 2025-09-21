#include "data/holders/SectorHistoryData.h"

#include <cstdint>
#include <vector>
#include <map>
#include "data/internal/Lap.h"
#include "data/internal/Sector.h"
#include "data/holders/TrackData.h"
#include "detectors/SectorStateChanged.h"
#include "utilities/Sector.h"




Processor::Data::SectorHistoryData::SectorHistoryData(const bool isMinisector,
    const Processor::Data::TrackData& trackDataReference) :
    m_sectors(),
    m_personalBestSectorMap(),
    m_trackDataReference(trackDataReference),
    m_minisector(isMinisector),
    m_isDataComplete(true),
    m_installedChangedSectorStateDetector(nullptr) {

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

        case Processor::Detector::Type::SectorStateChanged:
            m_installedChangedSectorStateDetector = dynamic_cast<Processor::Detector::SectorStateChanged*>(detector);
            return true;

        default:
            // do nothing
            return false;

    }

}



const bool Processor::Data::SectorHistoryData::Initialized() const {

    return !m_sectors.empty();

}



const bool Processor::Data::SectorHistoryData::Finalized() const {

    return m_isDataComplete;

}



void Processor::Data::SectorHistoryData::initialize(const uint8_t driverID) {

    if (Initialized()) return;

    auto sectors = m_trackDataReference.copySectors();
    auto minisectors = m_trackDataReference.copyMiniSectors();
    if (sectors.empty() || minisectors.empty()) return;

    // initialize the first sector in the vector
    if (m_minisector) {

        Lap::Internal::Sector newMinisector{
            driverID,
            minisectors.begin()->getLapOrderID(),
            0,
            minisectors.size(),
            sectors.begin()->getParentID(),
            minisectors.begin()->getParentOrderID(),
            minisectors.begin()->getStartPoint(),
            minisectors.begin()->getEndPoint(),
            0 };

        initializeSector(newMinisector, 0, Lap::Internal::Status::InvalidUnknown);
        m_sectors.emplace(0, newMinisector);

    }
    else {

        Lap::Internal::Sector newSector{
            driverID,
            sectors.begin()->getLapOrderID(),
            0,
            sectors.size(),
            sectors.begin()->getStartPoint(),
            sectors.begin()->getEndPoint()};

        initializeSector(newSector, 0, Lap::Internal::Status::InvalidUnknown);
        m_sectors.emplace(0, newSector);

    }

    m_isDataComplete = false;

}



void Processor::Data::SectorHistoryData::update(const uint8_t id, float_t lapDistanceRun,
    const Lap::Internal::Time currentLapTime, const Lap::Internal::Status status, const bool isValid) {

    // function is only meant to be used for minisectors
    if (!m_minisector ||
        m_sectors.empty() ||
        m_isDataComplete ||
        (status == Lap::Internal::Status::InvalidUnknown)) return;
    bool createNew = (m_sectors.size() == 1);

    auto& currentSector = m_sectors.rbegin()->second;
    createNew |= updateSector(currentSector, lapDistanceRun, currentLapTime, status, isValid);    
    if (createNew) {

        // Initialize new sectors, and add them to the overall map and to the lap data
        auto sectors = m_trackDataReference.copySectors();
        auto minisectors = m_trackDataReference.copyMiniSectors();
        const uint16_t lapID = std::floor(m_sectors.size() / minisectors.size()) + 1;

        // HACK: because in some sims the outlap at the start of quali comes with negative distance run, we need to find a way to calculate
        // how much distance was actually covered on this outlap
        // I really don't understand why they took this absolute assbackwards way of handling outlaps...
        // Even after that we need to guarantee that the distance is not negative
        if (lapDistanceRun < 0.0f) {

            lapDistanceRun += Processor::Utility::Sector::getTotalLapDistanceFromSectors(minisectors);
            lapDistanceRun = std::fmax(0.01f, lapDistanceRun);

        }

        const auto& currentSectorTemplate = Processor::Utility::Sector::getSectorByDistance(sectors, lapDistanceRun);
        const auto& currentMinisectorTemplate = Processor::Utility::Sector::getSectorByDistance(minisectors, lapDistanceRun);

        Lap::Internal::Sector newMinisector{
            id,
            currentMinisectorTemplate.getLapOrderID(),
            static_cast<uint16_t>(lapID - 1),
            minisectors.size(),
            currentSectorTemplate.getLapOrderID(),
            currentMinisectorTemplate.getParentOrderID(),
            currentMinisectorTemplate.getStartPoint(),
            currentMinisectorTemplate.getEndPoint(),
            currentLapTime };

        initializeSector(newMinisector, currentLapTime, status);
        m_sectors.emplace(newMinisector.getUniqueOverallID(), newMinisector);
        m_installedChangedSectorStateDetector->addChangedSectorInfo(newMinisector);

    }

}



void Processor::Data::SectorHistoryData::update(const uint8_t id, float_t lapDistanceRun,
    const std::vector<Lap::Internal::Time>& sectorTimes, const Lap::Internal::Status status, const bool isValid) {

    // function is only meant to be used for sectors
    if (m_minisector ||
        m_sectors.empty() ||
        sectorTimes.empty() ||
        m_isDataComplete ||
        (status == Lap::Internal::Status::InvalidUnknown)) return;
    bool createNew = (m_sectors.size() == 1);

    auto& currentSector = m_sectors.rbegin()->second;
    createNew |= updateSector(currentSector, lapDistanceRun, sectorTimes[currentSector.getLapOrderID() - 1], status, isValid);
    if (createNew) {

        // Initialize new sectors, and add them to the overall map and to the lap data
        auto sectors = m_trackDataReference.copySectors();
        const uint16_t lapID = std::floor(m_sectors.size() / sectors.size()) + 1;

        // HACK: because in some sims the outlap at the start of quali comes with negative distance run, we need to find a way to calculate
        // how much distance was actually covered on this outlap
        // I really don't understand why they took this absolute assbackwards way of handling outlaps...
        // Even after that we need to guarantee that the distance is not negative
        if (lapDistanceRun < 0.0f) {

            lapDistanceRun += Processor::Utility::Sector::getTotalLapDistanceFromSectors(sectors);
            lapDistanceRun = std::fmax(0.01f, lapDistanceRun);

        }
        const auto& currentSectorTemplate = Processor::Utility::Sector::getSectorByDistance(sectors, lapDistanceRun);

        Lap::Internal::Sector newSector{
            id,
            currentSectorTemplate.getLapOrderID(),
            0,
            sectors.size(),
            currentSectorTemplate.getStartPoint(),
            currentSectorTemplate.getEndPoint()};

        initializeSector(newSector, sectorTimes[0], status);
        m_sectors.emplace(newSector.getUniqueOverallID(), newSector);
        m_installedChangedSectorStateDetector->addChangedSectorInfo(newSector);

    }

}



void Processor::Data::SectorHistoryData::updateStatus(const uint8_t id, const Participant::Internal::Status status) {

    if (status == Participant::Internal::Status::DNF || status == Participant::Internal::Status::DSQ) {

        auto& currentSector = m_sectors.rbegin()->second;

        currentSector.m_status = Lap::Internal::Status::Retired;
        currentSector.m_performance = Lap::Internal::Performance::FinishedRetired;
        evaluateFinishedSector(currentSector);
        m_isDataComplete = true;

    }
    else if (status == Participant::Internal::Status::FinishedSession) {

        auto& currentSector = m_sectors.rbegin()->second;

        currentSector.m_status = Lap::Internal::Status::Finished;
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
        m_isDataComplete = true;

    }

}



void Processor::Data::SectorHistoryData::initializeSector(Lap::Internal::Sector& sector,
    const Lap::Internal::Time currentLapTime, const Lap::Internal::Status lapStatus) {

    // Validate the sector first, and verify if it hasn't been inited yet
    if (!Processor::Utility::Sector::validate(sector)) return;

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



bool Processor::Data::SectorHistoryData::updateSector(Lap::Internal::Sector& currentSector, float_t lapDistanceRun,
    const Lap::Internal::Time currentLapTime, const Lap::Internal::Status lapStatus, const bool isValid) {

    bool alwaysOverride = (currentSector.m_status == Lap::Internal::Status::InvalidUnknown);

    currentSector.m_finalLapTime = currentLapTime;
    if (alwaysOverride && (lapStatus == Lap::Internal::Status::FlyingLap) && isValid) {

        currentSector.m_status = Lap::Internal::Status::FlyingLap;
        currentSector.m_performance = Lap::Internal::Performance::CurrentlyRunning;
        m_installedChangedSectorStateDetector->addChangedSectorInfo(currentSector);

    }
    else if ((alwaysOverride || (currentSector.m_status == Lap::Internal::Status::FlyingLap)) &&
        (lapStatus == Lap::Internal::Status::FlyingLap) &&
        !isValid) {

        currentSector.m_status = Lap::Internal::Status::FlyingLapInvalid;
        currentSector.m_performance = Lap::Internal::Performance::CurrentlyRunningInvalid;
        m_installedChangedSectorStateDetector->addChangedSectorInfo(currentSector);

    }
    // If the current sector is marked as flying or flying invalid, pits has priority
    else if ((alwaysOverride || (currentSector.m_status == Lap::Internal::Status::FlyingLap) ||
        (currentSector.m_status == Lap::Internal::Status::FlyingLapInvalid)) &&
        (lapStatus == Lap::Internal::Status::InPits)) {

        currentSector.m_status = Lap::Internal::Status::InPits;
        currentSector.m_performance = Lap::Internal::Performance::CurrentlyRunningPits;
        m_installedChangedSectorStateDetector->addChangedSectorInfo(currentSector);

    }
    // HACK: because in some sims the outlap at the start of quali comes with negative distance run, we need to find a way to calculate
    // how much distance was actually covered on this outlap
    // I really don't understand why they took this absolute assbackwards way of handling outlaps...
    if (lapDistanceRun < 0.0f) {
        
        if (m_minisector) lapDistanceRun += Processor::Utility::Sector::getTotalLapDistanceFromSectors(m_trackDataReference.copyMiniSectors());
        else lapDistanceRun += Processor::Utility::Sector::getTotalLapDistanceFromSectors(m_trackDataReference.copySectors());
        
    }

    if (lapDistanceRun >= currentSector.getEndPoint()) {

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
        return true;

    }
    return false;

}



void Processor::Data::SectorHistoryData::evaluateFinishedSector(Lap::Internal::Sector& finishedSector) {

    if (!m_installedChangedSectorStateDetector || finishedSector.getUniqueOverallID() == 0) return;

    // check if this new finished sector is the fastest in the session
    // if it is, it's also this driver's PB
    if (m_installedChangedSectorStateDetector->checkFastestInSession(finishedSector)) {

        m_personalBestSectorMap[finishedSector.getLapOrderID()] = finishedSector.getUniqueOverallID();

    }
    else {

        // check if this is a new personal best for this driver
        // first get the overallUniqueID of the sector object with the fastest lap for this finished sector's lapOrderID
        auto overallIdIt = m_personalBestSectorMap.find(finishedSector.getLapOrderID());
        if (overallIdIt != m_personalBestSectorMap.end()) {

            // Now get the actual sector object and check times
            auto sectorIt = m_sectors.find(overallIdIt->second);
            if (sectorIt != m_sectors.end()) {

                auto fastestSectorTime = sectorIt->second.totalTime();
                auto currentSectorTime = finishedSector.totalTime();

                if (currentSectorTime.valid() &&
                    currentSectorTime < fastestSectorTime) {

                    m_personalBestSectorMap[finishedSector.getLapOrderID()] = finishedSector.getUniqueOverallID();
                    finishedSector.m_performance = Lap::Internal::Performance::FinishedPersonalBest;

                }
                if (currentSectorTime.valid() &&
                    (currentSectorTime > (fastestSectorTime * 1.2f)) &&
                    (currentSectorTime > (fastestSectorTime + 1000))) {

                    finishedSector.m_status = Lap::Internal::Status::SlowLap;

                }

                m_installedChangedSectorStateDetector->addChangedSectorInfo(finishedSector);

            }

        }

    }

}