#include "data/DriverState.h"

#include <cstdint>
#include <vector>
#include "data/holders/LapInfo.h"
#include "data/holders/WarningPenaltyData.h"
#include "data/holders/PositionTimingData.h"
#include "detectors/Interface.h"
#include "detectors/DriverStatus.h"
#include "detectors/Overtake.h"
#include "detectors/WarningPenalty.h"
#include "detectors/Type.h"



Processor::Data::DriverState::DriverState(const uint8_t id, const uint8_t startingPosition) :
    m_id(id),
    m_posTimeData(startingPosition),
    m_warnPenData(),
    m_laps(),
    m_installedOvertakeDetector(nullptr),
    m_installedPenWarnDetector(nullptr),
    m_installedStatusDetector(nullptr) {




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