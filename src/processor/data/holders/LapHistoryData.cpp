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
#include "detectors/SectorStateChanged.h"
#include "detectors/Type.h"
#include "detectors/TyreChanged.h"
#include "utilities/Sector.h"




Processor::Data::LapHistoryData::LapHistoryData(const Processor::Data::TrackData& trackData) :
    m_laps(),
    m_defaultNumSectors(trackData.copySectors().size()),
    m_totalTime(),
    m_isDataComplete(false),
    m_fastestLapID(UINT16_MAX),
    m_installedFinishedLapDetector(nullptr),
    m_installedTyreChangeDetector(nullptr),
    m_installedChangedSectorStateDetector(nullptr) {

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

        case Processor::Detector::Type::SectorStateChanged:
            m_installedChangedSectorStateDetector =
                dynamic_cast<Processor::Detector::SectorStateChanged*>(detector);
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
    lap.m_numSectorsInLap = m_defaultNumSectors;
    for (size_t i = 1; i <= m_defaultNumSectors; ++i) {

        // init lap ID 0 sectors
        lap.m_sectors.push_back(Lap::Internal::SimpleSector(driverID, 0, i, lap.m_numSectorsInLap));

    }
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



void Processor::Data::LapHistoryData::updateLap(const uint8_t id, const uint8_t lapID,
    const uint8_t numSectorsInLap, const Lap::Internal::Status lapStatus,
    const Lap::Internal::Time currentLapTime, const std::vector<Lap::Internal::Time> sectorTimes,
    const uint8_t sectorsComplete, const bool isValid, const Lap::Internal::Time previousLapTime,
    const Participant::Internal::Status participantStatus) {

    // Only add new info if we know we still have missing info
    if (!m_isDataComplete) {

        // new entry creation should always happen if the map is empty
        // realistically, this createNewLap would be normally initialized as "false" because
        // it is expected that LapHistoryData::initialize() is called first
        bool createNewLap = m_laps.empty();
        Tyre::Internal::Data tyreData;

        // First try to find the lap with the same ID, alter it
        auto it = m_laps.find(lapID);
        if (it != m_laps.end()) {

            auto& lap = it->second;
            if (!lap.m_isFinished) {

                // Process current sector changes (use lap.m_numSectorsComplete as index)
                // If the last registered sector was completed, as noted by the difference in the current sector index, 
                // then also modify its data to keep it as up-to-date as possible, making sure to not mark it as completed
                const bool wasSectorCompleted = (sectorsComplete != lap.m_numSectorsComplete);
                evaluateSectorChanges(lap.m_sectors[lap.m_numSectorsComplete], lapStatus, participantStatus,
                    isValid, sectorTimes[lap.m_numSectorsComplete], wasSectorCompleted);
                if (wasSectorCompleted) {

                    evaluateSectorChanges(lap.m_sectors[sectorsComplete], lapStatus, participantStatus,
                        isValid, sectorTimes[sectorsComplete], false);

                }

                // Process current lap changes, be careful to update its number of sectors complete so
                // on the next set of info, we update the correct sector
                lap.m_totalLapTime = currentLapTime;
                lap.m_status = lapStatus;
                lap.m_isValid = isValid;
                lap.m_numSectorsComplete = sectorsComplete;
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
            auto finalSectorTime = previousLapTime;
            for (const auto& sector : finishedLap.m_sectors) {

                finalSectorTime -= sector.m_time;

            }
            evaluateSectorChanges(finishedLap.m_sectors[finishedLap.m_sectors.size() - 1], finishedLap.m_status,
                participantStatus, finishedLap.m_isValid, finalSectorTime, true);
            evaluateFinishedLap(finishedLap);

            // record this finished lap's tyre usage to transmit the information to the next one
            tyreData = finishedLap.m_tyre;

        }
        // Either if a new lap has just been started, or if the map is empty, we need to create a new lap entry
        if (createNewLap) {

            // initialize lap and sectors information
            Processor::Data::LapInfo lap;
            lap.m_driverId = id;
            lap.m_lapId = lapID;
            lap.m_isFinished = false;
            lap.m_numSectorsInLap = numSectorsInLap;
            for (size_t i = 1; i <= lap.m_numSectorsInLap; ++i) {

                lap.m_sectors.push_back(Lap::Internal::SimpleSector(id, lapID, i, lap.m_numSectorsInLap));
                if (m_personalBestSectorMap.size() < lap.m_numSectorsInLap) {

                    m_personalBestSectorMap.emplace(i, 0);

                }

            }

            // Process current sector changes (use lap.m_numSectorsComplete as index)
            evaluateSectorChanges(lap.m_sectors[sectorsComplete], lapStatus, participantStatus,
                isValid, sectorTimes[sectorsComplete], false);

            // Process current lap changes, be careful to update its number of sectors complete so
            // on the next set of info, we update the correct sector
            lap.m_totalLapTime = currentLapTime;
            lap.m_status = lapStatus;
            lap.m_isValid = isValid;
            lap.m_numSectorsComplete = sectorsComplete;

            // increment tyre age before setting it
            // note that the ID has not been set just to guarantee comparison when tyre data is received
            ++tyreData.m_stintLength;
            lap.m_tyre = tyreData;

            m_laps.emplace(lap.m_lapId, lap);

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



void Processor::Data::LapHistoryData::evaluateSectorChanges(Lap::Internal::SimpleSector& currentSector,
    const Lap::Internal::Status lapStatus, const Participant::Internal::Status participantStatus,
    const bool isValid, const Lap::Internal::Time sectorTime, const bool sectorComplete) {

    bool alwaysOverride = (currentSector.m_status == Lap::Internal::Status::InvalidUnknown);

    // Update sector time
    currentSector.m_time = sectorTime;
    // Determine what state changes may be done, and which are required
    bool canChangeToInvalid = (currentSector.m_status == Lap::Internal::Status::FlyingLap);
    bool statusInvalid = (lapStatus == Lap::Internal::Status::FlyingLap) && !isValid;
    bool canChangeToInPits = (canChangeToInvalid || (currentSector.m_status == Lap::Internal::Status::FlyingLapInvalid));
    bool statusInPits = (lapStatus == Lap::Internal::Status::InPits);
    bool canChangeToRetired = (canChangeToInPits || (currentSector.m_status == Lap::Internal::Status::InPits));
    bool statusRetired =
        ((participantStatus == Participant::Internal::Status::DNF) || (participantStatus == Participant::Internal::Status::DSQ));
    bool changedToRetired = false;

    // Priority 1: participant status change
    if ((alwaysOverride || canChangeToRetired) && statusRetired) {

        changedToRetired = true;
        currentSector.m_status = Lap::Internal::Status::Retired;
        currentSector.m_performance = Lap::Internal::Performance::FinishedRetired;
        m_installedChangedSectorStateDetector->addChangedSectorInfo(currentSector);

    }
    // Priority 2.1: pit status change (pit-out branch)
    else if ((alwaysOverride || canChangeToInPits) && statusInPits && currentSector.isFirstSectorInLap()) {

        currentSector.m_status = Lap::Internal::Status::InPits;
        currentSector.m_performance = Lap::Internal::Performance::CurrentlyRunningPitOut;
        m_installedChangedSectorStateDetector->addChangedSectorInfo(currentSector);

    }
    // Priority 2.2: pit status change (pit-in branch)
    else if ((alwaysOverride || canChangeToInPits) && statusInPits && currentSector.isLastSectorInLap()) {

        currentSector.m_status = Lap::Internal::Status::InPits;
        currentSector.m_performance = Lap::Internal::Performance::CurrentlyRunningPitIn;
        m_installedChangedSectorStateDetector->addChangedSectorInfo(currentSector);

    }
    // Priority 3: lap validity status change
    else if ((alwaysOverride || canChangeToInvalid) && statusInvalid) {

        currentSector.m_status = Lap::Internal::Status::FlyingLapInvalid;
        currentSector.m_performance = Lap::Internal::Performance::CurrentlyRunningInvalid;
        m_installedChangedSectorStateDetector->addChangedSectorInfo(currentSector);

    }
    // Priority 4: default case in which the sector was just started
    else if (alwaysOverride && (lapStatus == Lap::Internal::Status::FlyingLap) && isValid) {

        currentSector.m_status = Lap::Internal::Status::FlyingLap;
        currentSector.m_performance = Lap::Internal::Performance::CurrentlyRunning;
        m_installedChangedSectorStateDetector->addChangedSectorInfo(currentSector);

    }
    // Determine current sector completion (no further updates)
    // NOTE: Right now this is not triggered for the last sector due to integration
    if (sectorComplete || changedToRetired) {

        switch (currentSector.m_performance) {

            case Lap::Internal::Performance::CurrentlyRunning:
                currentSector.m_performance = Lap::Internal::Performance::FinishedNormal;
                break;

            case Lap::Internal::Performance::CurrentlyRunningPitOut:
                currentSector.m_performance = Lap::Internal::Performance::FinishedPitOut;
                break;

            case Lap::Internal::Performance::CurrentlyRunningPitIn:
                currentSector.m_performance = Lap::Internal::Performance::FinishedPitIn;
                break;

            case Lap::Internal::Performance::CurrentlyRunningInvalid:
                currentSector.m_performance = Lap::Internal::Performance::FinishedInvalid;
                break;

            default:
                // do nothing, these are the only expected statuses if we've just finished this sector
                break;

        }

        evaluateFinishedSector(currentSector);

    }
    // TODO what if the sector is the last one?
    // TODO what if this is quali, as the lap ID does not increment?
    // TODO what if this is race and formation lap?

}



void Processor::Data::LapHistoryData::evaluateFinishedSector(Lap::Internal::SimpleSector& finishedSector) {

    if (!m_installedChangedSectorStateDetector ||
        !Processor::Utility::Sector::validate(finishedSector)) return;

    // check if this new finished sector is the fastest in the session
    // if it is, it's also this driver's PB
    if (m_installedChangedSectorStateDetector->checkFastestInSession(finishedSector)) {

        m_personalBestSectorMap[finishedSector.getSectorID()] = finishedSector.getLapID();

    }
    else {

        // check if this is a new personal best for this driver
        // first get the ID of the lap in which the personal best sector time was reached, for this finished sector's ID
        auto lapIDIt = m_personalBestSectorMap.find(finishedSector.getSectorID());
        if (lapIDIt != m_personalBestSectorMap.end()) {

            // Now get the lap object
            auto lapIt = m_laps.find(lapIDIt->second);
            if (lapIt != m_laps.end()) {

                auto referenceSector = lapIt->second.m_sectors.at(finishedSector.getSectorID() - 1);
                auto fastestSectorTime = referenceSector.m_time;
                auto currentSectorTime = finishedSector.m_time;

                // if the currently registered personal best sector is invalid, then any valid sector is a new PB
                if ((finishedSector.m_performance != Lap::Internal::Performance::FinishedPitOut) &&
                    (finishedSector.m_performance != Lap::Internal::Performance::FinishedPitIn) &&
                    (finishedSector.m_performance != Lap::Internal::Performance::FinishedInvalid) &&
                    (finishedSector.m_performance != Lap::Internal::Performance::FinishedRetired) &&
                    (finishedSector.m_performance != Lap::Internal::Performance::InvalidUnknown) &&
                    currentSectorTime.valid() &&
                    (!fastestSectorTime.valid() || (currentSectorTime < fastestSectorTime))) {

                    finishedSector.m_performance = Lap::Internal::Performance::FinishedPersonalBest;
                    m_personalBestSectorMap[finishedSector.getSectorID()] = finishedSector.getLapID();

                }
                if (currentSectorTime.valid() && fastestSectorTime.valid() &&
                    (currentSectorTime > (fastestSectorTime * 1.2f))) {

                    finishedSector.m_status = Lap::Internal::Status::SlowLap;

                }

            }
            else {

                // if this sector ID could not be found, then at least insert the current ID to primer the personal best sector map
                m_personalBestSectorMap.insert_or_assign(finishedSector.getSectorID(), finishedSector.getLapID());

            }

            m_installedChangedSectorStateDetector->addChangedSectorInfo(finishedSector);

        }

    }

}