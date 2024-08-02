#include "data/DriverState.h"

#include <cstdint>
#include <map>
#include <vector>
#include "data/holders/LapInfo.h"
#include "data/holders/WarningPenaltyData.h"
#include "data/holders/PositionTimingData.h"
#include "detectors/Interface.h"
#include "detectors/DriverStatus.h"
#include "detectors/FinishedLap.h"
#include "detectors/Overtake.h"
#include "detectors/WarningPenalty.h"
#include "detectors/Type.h"



Processor::Data::DriverState::DriverState(const uint8_t id, const uint8_t startingPosition) :
    m_id(id),
    m_posTimeData(startingPosition),
    m_warnPenData(),
    m_installedOvertakeDetector(nullptr),
    m_installedPenWarnDetector(nullptr),
    m_installedStatusDetector(nullptr),
    m_installedFinishedLapDetector(nullptr) {




}



Processor::Data::DriverState::~DriverState() {




}



void Processor::Data::DriverState::installDetector(Processor::Detector::Interface* detector) {

    if (!detector) return;

    switch (detector->GetType()) {

        case Processor::Detector::Type::Overtake:
            m_installedOvertakeDetector = dynamic_cast<Processor::Detector::Overtake*>(detector);
            break;

        case Processor::Detector::Type::FastestLap:
            // TODO implement
            break;

        case Processor::Detector::Type::WarningPenalty:
            m_installedPenWarnDetector = dynamic_cast<Processor::Detector::WarningPenalty*>(detector);
            break;

        case Processor::Detector::Type::ParticipantStatus:
            m_installedStatusDetector = dynamic_cast<Processor::Detector::DriverStatus*>(detector);
            break;

        default:
            // shit's fucked
            break;

    }

}



void Processor::Data::DriverState::updateCurrentPosition(const uint8_t currentPosition) {

    // Only add a position change if it actually exists
    if (m_posTimeData.m_currentPosition != currentPosition) {

        if (m_installedOvertakeDetector) {

            m_installedOvertakeDetector->AddPositionChange(m_id,
                m_posTimeData.m_currentPosition, currentPosition);

        }

        m_posTimeData.m_currentPosition = currentPosition;

    }

}



void Processor::Data::DriverState::updateWarningPenalties(const uint8_t totalWarnings,
        const uint8_t trackLimitWarnings, const uint16_t timePenalties,
        const uint8_t stopGoPens, const uint8_t driveThroughPens) {

    const int8_t diffTotalWarns = totalWarnings - m_warnPenData.m_totalWarns;
    const int8_t diffTrackLimWarns = trackLimitWarnings - m_warnPenData.m_numTrackLimits;
    const int32_t diffTimePen = timePenalties - m_warnPenData.m_timePenMS;
    const int8_t diffStopGo = stopGoPens - m_warnPenData.m_numStopGo;
    const int8_t diffDriveThrough = driveThroughPens - m_warnPenData.m_numDriveThrough;

    // Only pass information to the detector if there are indeed changes in state
    if ((diffTotalWarns != 0) || (diffTrackLimWarns != 0) || (diffTimePen != 0) ||
            (diffStopGo != 0) || (diffDriveThrough != 0)) {

        if (m_installedPenWarnDetector) {

            m_installedPenWarnDetector->AddWarnPenChange(m_id, diffTotalWarns,
                diffTrackLimWarns, diffTimePen, diffStopGo, diffDriveThrough);

        }

        // Update information
        if (diffTotalWarns != 0) m_warnPenData.m_totalWarns = totalWarnings;
        if (diffTrackLimWarns != 0) m_warnPenData.m_numTrackLimits = trackLimitWarnings;
        if (diffTimePen != 0) m_warnPenData.m_timePenMS = timePenalties;
        if (diffStopGo != 0) m_warnPenData.m_numStopGo = stopGoPens;
        if (diffDriveThrough != 0) m_warnPenData.m_numDriveThrough = driveThroughPens;

    }

}



void Processor::Data::DriverState::updateStatus(const Participant::Internal::Status status) {

    if (m_posTimeData.m_status != status &&
        m_posTimeData.m_status != Participant::Internal::Status::DNF &&
        m_posTimeData.m_status != Participant::Internal::Status::DSQ &&
        m_posTimeData.m_status != Participant::Internal::Status::FinishedSession) {

        // Update information
        m_posTimeData.m_status = status;

        // Feed to detector
        m_installedStatusDetector->AddStatusChange(m_id, status);

    }

}


void Processor::Data::DriverState::updateLap(const uint8_t lapID, const Lap::Internal::Type type,
    const Lap::Internal::Status status, const std::vector<Lap::Internal::Time> sectorTimes,
    const float_t lapDistanceRun, const Lap::Internal::Time previousLapTime) {

    // new entry creation should always happen if the map is empty
    bool createNew = m_lapData.m_laps.empty();

    // First find the lap with the same ID, alter it
    auto it = m_lapData.m_laps.find(lapID);
    if (it != m_lapData.m_laps.end()) {

        auto& lap = it->second;
        if (!lap.m_isFinished) {

            lap.m_sector1Time = sectorTimes.at(0);
            lap.m_sector2Time = sectorTimes.at(1);
            lap.m_sector3Time = sectorTimes.at(2);
            lap.m_totalLapTime = lap.m_sector1Time + lap.m_sector2Time + lap.m_sector3Time;
            lap.m_status = status;
            lap.m_distanceFulfilled = lapDistanceRun;

        }

    }
    // If unsuccessful, find the previous lap
    // If still unsuccessful, then it's the first lap so we need to create an entry
    else if ((it = m_lapData.m_laps.find(lapID - 1)) != m_lapData.m_laps.end()) {
        
        createNew = true;
        auto& finishedLap = it->second;
        finishedLap.m_isFinished = true;
        finishedLap.m_totalLapTime = previousLapTime;
        finishedLap.m_sector3Time = finishedLap.m_totalLapTime - finishedLap.m_sector1Time - finishedLap.m_sector2Time;

        m_installedFinishedLapDetector->addNewLap(it->second);

    }
    if (createNew) {

        Processor::Data::LapInfo lap;
        lap.m_lapId = lapID;
        lap.m_sector1Time = sectorTimes.at(0);
        lap.m_sector2Time = sectorTimes.at(1);
        lap.m_sector3Time = sectorTimes.at(2);
        lap.m_totalLapTime = lap.m_sector1Time + lap.m_sector2Time + lap.m_sector3Time;
        lap.m_status = status;
        lap.m_distanceFulfilled = lapDistanceRun;
        m_lapData.m_laps.emplace(lap.m_lapId, lap);

    }

}