#include "data/holders/LapHistoryData.h"

#include <cmath>
#include <cstdint>
#include <limits>
#include <map>
#include "data/holders/LapInfo.h"
#include "data/holders/TrackData.h"
#include "data/internal/Participant.h"
#include "data/internal/Tyre.h"
#include "detectors/LapFinished.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"
#include "detectors/TyreChanged.h"
#include "utilities/Sector.h"




Processor::Data::LapHistoryData::LapHistoryData(const Processor::Data::TrackData& trackDataReference) :
    m_laps(),
    m_totalTime(),
    m_isDataComplete(false),
    m_fastestLapID(UINT16_MAX),
    m_personalBestSectorMap(),
    m_personalBestMiniSectorMap(),
    m_trackDataReference(trackDataReference),
    m_installedFinishedLapDetector(nullptr),
    m_installedTyreChangeDetector(nullptr) {

    // Build PB sector and minisector map based on trackdata
    // Default PB lap is 0 for sectors and minisectors both
    const auto& s = trackDataReference.copySectors();
    const auto& ms = trackDataReference.copyMiniSectors();

    for (const auto& sector : s) {

        m_personalBestSectorMap.emplace(sector.getLapOrderID(), 0);

    }

    for (const auto& minisector : ms) {

        m_personalBestMiniSectorMap.emplace(minisector.getLapOrderID(), 0);

    }

}



bool Processor::Data::LapHistoryData::installDetector(Processor::Detector::Interface* detector) {

    if (!detector) return false;

    switch (detector->GetType()) {

        case Processor::Detector::Type::LapFinished:
            m_installedFinishedLapDetector = dynamic_cast<Processor::Detector::LapFinished*>(detector);
            return true;

        case Processor::Detector::Type::TyreChanged:
            m_installedTyreChangeDetector = dynamic_cast<Processor::Detector::TyreChanged*>(detector);
            return true;

        default:
            // do nothing
            return false;

    }

}



const bool Processor::Data::LapHistoryData::Initialized() const {

    // initial settings should always have the ID of 0
    const auto it = m_laps.find(0);
    if (it == m_laps.end())
        return false;

    // check if the lap's settings diverge from default values
    return (it->second.m_tyre.m_stintNo > 0) && (it->second.m_tyre.m_stintNo != UINT8_MAX) &&
        (it->second.m_driverId != UINT8_MAX) && (it->second.m_lapId != UINT16_MAX) &&
        (it->second.m_tyre.m_actualTyre != Tyre::Internal::Actual::InvalidUnknown) &&
        (it->second.m_tyre.m_visualTyre != Tyre::Internal::Visual::InvalidUnknown);

}



const bool Processor::Data::LapHistoryData::Finalized() const {

    return m_isDataComplete;

}



void Processor::Data::LapHistoryData::initialize(const uint8_t driverID, const Tyre::Internal::Data data) {

    // create new lap entry only if there are no laps yet; we only want 1 lap with ID 0
    if (!m_laps.empty()) return;

    Processor::Data::LapInfo lap;
    lap.m_driverId = driverID;
    lap.m_lapId = 0;
    lap.m_tyre = data;
    m_laps.emplace(lap.m_lapId, lap);

}



void Processor::Data::LapHistoryData::completeData(const uint8_t id, const uint8_t numLaps, Lap::Internal::Time sessionTime) {

    if (!m_isDataComplete) {

        // check for the final lap entry
        auto it = m_laps.rbegin();
        if (it != m_laps.rend()) {

            auto& lap = it->second;

            // now that we know how many laps this driver did from the game (source of truth), we can validate whether
            // all data is complete
            // this should also work well enough in the case of early retirement
            if (lap.m_isFinished) {

                m_isDataComplete = true;

            }
            else {

                // extract the final lap's lap time from the total time
                lap.m_totalLapTime = sessionTime - m_totalTime;
                evaluateFinishedLap(lap);
                m_isDataComplete = true;

            }

        }

    }

}



void Processor::Data::LapHistoryData::updateLap(const uint8_t id, const uint8_t lapID, const Lap::Internal::Status lapStatus,
    const Lap::Internal::Time currentLapTime, const std::vector<Lap::Internal::Time> sectorTimes,
    const float_t lapDistanceRun, const Lap::Internal::Time previousLapTime, const Participant::Internal::Status participantStatus) {

    // Only add new info if we know we still have missing info
    if (!m_isDataComplete) {

        // new entry creation should always happen if the map is empty
        bool createNewLap = m_laps.empty();
        bool createNewSector = m_sectors.empty();
        bool createNewMinisector = m_minisectors.empty();
        Tyre::Internal::Data tyreData;

        // First try to find the lap with the same ID, alter it
        auto it = m_laps.find(lapID);
        if (it != m_laps.end()) {

            auto& lap = it->second;
            if (!lap.m_isFinished) {

                // TODO rework with sector structs
                lap.m_totalLapTime.zero();
                lap.m_totalLapTime = currentLapTime;
                lap.m_status = lapStatus;
                lap.m_distanceFulfilled = lapDistanceRun;

                auto& currentSector = m_sectors.rbegin()->second;
                auto& previousSector = currentSector;
                if (m_sectors.size() > 1) {

                    previousSector = std::prev(m_sectors.rbegin())->second;

                }
                auto& currentMiniSector = m_minisectors.rbegin()->second;
                auto& previousMiniSector = currentMiniSector;
                if (m_sectors.size() > 1) {

                    previousMiniSector = std::prev(m_minisectors.rbegin())->second;

                }
                updateSector(previousSector, currentSector, lap.m_totalLapTime, lap.m_status);
                updateSector(previousMiniSector, currentMiniSector, lap.m_totalLapTime, lap.m_status);
                if (lap.m_distanceFulfilled >= currentSector.getEndPoint()) {

                    // TODO what do when sector finished, aside from creating a new one + minisector?
                    createNewSector = true;

                }
                if (lap.m_distanceFulfilled >= currentMiniSector.getEndPoint()) {

                    // TODO what do when minisector finished
                    createNewMinisector = true;

                }


                if (participantStatus == Participant::Internal::Status::DNF ||
                    participantStatus == Participant::Internal::Status::DSQ) {

                    lap.m_isFinished = true;
                    lap.m_isValid = false;
                    evaluateFinishedLap(lap);
                    m_isDataComplete = true;

                }

            }

        }
        // If unsuccessful, that means there's a new lap, so a new entry will have to be created
        // first, find the previous lap and finalize its entry
        else if ((it = m_laps.find(lapID - 1)) != m_laps.end()) {

            createNewLap = true;
            auto& finishedLap = it->second;
            finishedLap.m_isFinished = true;
            finishedLap.m_totalLapTime = previousLapTime;
            // TODO rework with sector structs
            evaluateFinishedLap(finishedLap);

            // record this finished lap's tyre usage to transmit the information to the next one
            tyreData = finishedLap.m_tyre;

        }
        // Either if a new lap has just been started, or if the map is empty, we need to create a new lap entry
        if (createNewLap) {

            Processor::Data::LapInfo lap;
            lap.m_driverId = id;
            lap.m_lapId = lapID;
            lap.m_isFinished = false;
            lap.m_totalLapTime = currentLapTime;
            lap.m_status = lapStatus;
            lap.m_distanceFulfilled = lapDistanceRun;

            // increment tyre age before setting it
            // note that the ID has not been set just to guarantee comparison when tyre data is received
            ++tyreData.m_stintLength;
            lap.m_tyre = tyreData;

            m_laps.emplace(lap.m_lapId, lap);
            createNewSector = true;
            createNewMinisector = true;

        }
        if (createNewSector) {

            // Initialize new sectors, and add them to the overall map and to the lap data
            auto sectors = m_trackDataReference.copySectors();
            const auto& currentSectorTemplate = Processor::Utility::Sector::getSectorByDistance(sectors, lapDistanceRun);
            Lap::Internal::Sector newSector{ currentSectorTemplate.getLapOrderID(),
                static_cast<uint16_t>(lapID - 1),
                sectors.size(),
                currentSectorTemplate.getStartPoint(),
                currentSectorTemplate.getEndPoint(),
                currentLapTime };
            initializeSector(newSector, currentLapTime, lapStatus);
            m_sectors.emplace(newSector.getUniqueOverallID(), newSector);

        }
        if (createNewMinisector) {

            auto sectors = m_trackDataReference.copySectors();
            auto minisectors = m_trackDataReference.copyMiniSectors();
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
            initializeSector(newMinisector, currentLapTime, lapStatus);
            m_minisectors.emplace(newMinisector.getUniqueOverallID(), newMinisector);
        }

    }

}



void Processor::Data::LapHistoryData::updateTyre(const uint8_t driverID, const Tyre::Internal::Data data) {

    // We always update the latest lap
    auto it = m_laps.find(m_laps.size() - 1);
    if (it == m_laps.end()) return;

    auto& currentLap = it->second;

    // TODO, how to detect the sector 3/sector 1 pitlane issue that influences perceived tyre age?
    if (currentLap.m_tyre.m_stintNo != data.m_stintNo) {

        // if the stint number has changed, then we can assume a tyre change has happened
        currentLap.m_tyre = data;
        if (m_installedTyreChangeDetector) {

            m_installedTyreChangeDetector->addTyreChangeInfo(currentLap.m_driverId, currentLap.m_tyre);

        }

    }

}



const Processor::Data::LapInfo* Processor::Data::LapHistoryData::getLapData(const uint16_t lapID) const {

    auto it = m_laps.find(lapID);
    if (it != m_laps.end()) {

        return &(it->second);

    }

    return nullptr;

}



const uint16_t Processor::Data::LapHistoryData::numLapsAvailable() const {

    return m_laps.size();

}


void Processor::Data::LapHistoryData::initializeSector(Lap::Internal::Sector& sector,
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



void Processor::Data::LapHistoryData::updateSector(Lap::Internal::Sector& previousSector, Lap::Internal::Sector& currentSector,
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



void Processor::Data::LapHistoryData::evaluateFinishedLap(const Processor::Data::LapInfo& finishedLap) {

    if (!m_installedFinishedLapDetector || finishedLap.m_lapId == 0) return;

    m_totalTime += finishedLap.m_totalLapTime;

    // check if this new fastest lap is the fastest in the session
    // if it is, it's also this driver's PB
    if (m_installedFinishedLapDetector->checkFastestInSession(finishedLap)) {

        m_fastestLapID = finishedLap.m_lapId;

    }
    else {

        // check if this is a new personal best for this driver
        // if there are no laps found with the ID, then it should mean that it is the first lap
        auto it = m_laps.find(m_fastestLapID);
        if (it != m_laps.end()) {

            const auto& fastestLap = it->second;
            if (finishedLap.m_isValid && finishedLap.m_totalLapTime.valid() &&
                (finishedLap.m_totalLapTime < fastestLap.m_totalLapTime)) {

                m_fastestLapID = finishedLap.m_lapId;
                m_installedFinishedLapDetector->addFinishedLapInfo(finishedLap, Lap::Internal::InfoType::PersonalBest);

            }
            else {

                m_installedFinishedLapDetector->addFinishedLapInfo(finishedLap, Lap::Internal::InfoType::LatestLap);

            }

        }
        else {

            m_fastestLapID = finishedLap.m_lapId;
            m_installedFinishedLapDetector->addFinishedLapInfo(finishedLap, Lap::Internal::InfoType::PersonalBest);

        }

    }

}