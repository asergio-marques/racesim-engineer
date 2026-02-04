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

                /*lap.m_status = lapStatus;
                lap.m_totalLapTime.zero();
                lap.m_totalLapTime = currentLapTime;
                lap.m_sectorTimes = sectorTimes;
                lap.m_isValid = isValid;
                if (lap.m_numSectorsComplete != sectorsComplete) {

                    evaluateFinishedSector(lap.m_numSectorsComplete, lap.m_sectorTimes[lap.m_numSectorsComplete],
                        lap.m_valid, lap.m_status == Lap::Internal::Status::Retired);
                    lap.m_numSectorsComplete = sectorsComplete;

                }

                if (participantStatus == Participant::Internal::Status::DNF ||
                    participantStatus == Participant::Internal::Status::DSQ) {

                    lap.m_isFinished = true;
                    lap.m_isValid = false;
                    evaluateFinishedSector(lap.m_numSectorsComplete, lap.m_sectorTimes[lap.m_numSectorsComplete], lap.m_status);
                    evaluateFinishedLap(lap);

                    m_isDataComplete = true;

                }*/

                lap.m_totalLapTime.zero();
                lap.m_totalLapTime = currentLapTime;
                // step 1 process current sector changes (use lap.m_numSectorsComplete as index)
                evaluateSectorChanges(lap.m_sectors[lap.m_numSectorsComplete], lapStatus, participantStatus,
                    isValid, sectorTimes[lap.m_numSectorsComplete], sectorsComplete != lap.m_numSectorsComplete);
                // step 1.1 time update sector
                // step 1.2 validity update                
                // step 1.3 pit status update
                // step 1.4 participant status update
                // step 1.5 extract performance changes and communicate to detector
                // step 2 process change of sectors
                // step 2.1 check difference of numSectorsComplete (make sure it is not 0 because 2 -> 0 means lap changed)
                // step 2.1.1 deduce finalized performance status from running performance status
                // step 2.1.2 communicate finalized sector data to detector
                // step 2.1.3 initialize data for new sector
                // step 2.1.4 communicate new sector data to detector
                // step 3 process lap changes
                // step 3.1 time update lap
                // step 3.2 validity update
                // step 3.3 participant status update (if DNF/DSQ close lap AND sector AND history data)
                evaluateLapChanges(lap, lapStatus, participantStatus, isValid);
                
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
    const bool isValid, Lap::Internal::Time sectorTime, const bool sectorComplete) {

    bool alwaysOverride = (currentSector.m_status == Lap::Internal::Status::InvalidUnknown);

    // step 1.1 time update sector
    currentSector.m_time = sectorTime;
    // step 1.2 determine updates required
    bool canChangeToInvalid = (currentSector.m_status == Lap::Internal::Status::FlyingLap);
    bool statusInvalid = (lapStatus == Lap::Internal::Status::FlyingLap) && !isValid;
    bool canChangeToInPits = (canChangeToInvalid || (currentSector.m_status == Lap::Internal::Status::FlyingLapInvalid));
    bool statusInPits = (lapStatus == Lap::Internal::Status::InPits);
    bool canChangeToRetired = (canChangeToInPits || (currentSector.m_status == Lap::Internal::Status::InPits));
    bool statusRetired =
        ((participantStatus == Participant::Internal::Status::DNF) || (participantStatus == Participant::Internal::Status::DSQ));
    bool changedToRetired = false;

    // step 1.3 initial status for unknown status of sector
    if (alwaysOverride && (lapStatus == Lap::Internal::Status::FlyingLap) && isValid) {

        currentSector.m_status = Lap::Internal::Status::FlyingLap;
        currentSector.m_performance = Lap::Internal::Performance::CurrentlyRunning;
        m_installedChangedSectorStateDetector->addChangedSectorInfo(currentSector);

    }
    // step 1.4 validity update
    else if ((alwaysOverride || canChangeToInvalid) && statusInvalid) {

        currentSector.m_status = Lap::Internal::Status::FlyingLapInvalid;
        currentSector.m_performance = Lap::Internal::Performance::CurrentlyRunningInvalid;
        m_installedChangedSectorStateDetector->addChangedSectorInfo(currentSector);

    }
    // step 1.5 pit status update
    else if ((alwaysOverride || canChangeToInPits) && statusInPits) {

        currentSector.m_status = Lap::Internal::Status::InPits;
        currentSector.m_performance = Lap::Internal::Performance::CurrentlyRunningPits;
        m_installedChangedSectorStateDetector->addChangedSectorInfo(currentSector);

    }
    // step 1.6 participant status update
    else if ((alwaysOverride || canChangeToRetired) && statusRetired) {

        changedToRetired = true;
        currentSector.m_status = Lap::Internal::Status::Retired;
        currentSector.m_performance = Lap::Internal::Performance::FinishedRetired;
        m_installedChangedSectorStateDetector->addChangedSectorInfo(currentSector);

    }
    if (sectorComplete || changedToRetired) {

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

        //evaluateFinishedSector(currentSector);

    }
    // TODO what if the sector is the last one?
    // TODO what if this is quali, as the lap ID does not increment?
    // TODO what if this is race and formation lap?

}




void Processor::Data::LapHistoryData::evaluateLapChanges(Processor::Data::LapInfo& changedLap,
    const Lap::Internal::Status newLapStatus, const Participant::Internal::Status newParticipantStatus,
    const bool newLapValidity) {



}