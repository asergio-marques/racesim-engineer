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
    m_fastestSector1LapID(UINT16_MAX),
    m_fastestSector2LapID(UINT16_MAX),
    m_fastestSector3LapID(UINT16_MAX),
    m_trackDataReference(trackDataReference),
    m_installedFinishedLapDetector(nullptr),
    m_installedTyreChangeDetector(nullptr) {



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
        bool createNew = m_laps.empty();
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

            createNew = true;
            auto& finishedLap = it->second;
            finishedLap.m_isFinished = true;
            finishedLap.m_totalLapTime = previousLapTime;
            // TODO rework with sector structs
            evaluateFinishedLap(finishedLap);

            // record this finished lap's tyre usage to transmit the information to the next one
            tyreData = finishedLap.m_tyre;

        }
        // Either if a new lap has just been started, or if the map is empty, we need to create a new lap entry
        if (createNew) {

            Processor::Data::LapInfo lap;
            lap.m_driverId = id;
            lap.m_lapId = lapID;
            lap.m_isFinished = false;
            lap.m_totalLapTime = currentLapTime;
            lap.m_status = lapStatus;
            lap.m_distanceFulfilled = lapDistanceRun;

            // work sectors and minisectors
            lap.m_sectors = m_trackDataReference.copySectors();
            auto& currentSector = Processor::Utility::Sector::getSectorByDistance(lap.m_sectors, lap.m_distanceFulfilled);
            auto& currentMinisector = Processor::Utility::Sector::getMiniSectorByDistance(lap.m_sectors, lap.m_distanceFulfilled);
            if (Processor::Utility::Sector::validate(currentSector) &&
                Processor::Utility::Sector::validate(currentMinisector)) {

                // set initial current sector parameters
                currentSector.m_currentTime = currentLapTime;
                if (lap.m_distanceFulfilled >=
                    (currentSector.m_endPoint - std::numeric_limits<float_t>::epsilon())) {

                    // TODO

                }
                // set initial current minisector parameters
                currentMinisector.m_currentTime = currentLapTime;
                if (lap.m_distanceFulfilled >=
                    (currentMinisector.m_endPoint - std::numeric_limits<float_t>::epsilon())) {

                    // TODO

                }

            }

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
        evaluateTyreDataChanged(currentLap);

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



void Processor::Data::LapHistoryData::evaluateTyreDataChanged(const Processor::Data::LapInfo& currentLap) {

    if (m_installedTyreChangeDetector) {

        m_installedTyreChangeDetector->addTyreChangeInfo(currentLap.m_driverId, currentLap.m_tyre);

    }

}