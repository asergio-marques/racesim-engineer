#include "data/DriverState.h"

#include <cstdint>
#include <map>
#include <vector>
#include "data/holders/LapInfo.h"
#include "data/holders/WarningPenaltyData.h"
#include "data/holders/PositionTimingData.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"



Processor::Data::DriverState::DriverState(const uint8_t id, const uint8_t startingPosition) :
    m_id(id),
    m_posTimeData(startingPosition),
    m_warnPenData() {




}



void Processor::Data::DriverState::installDetector(Processor::Detector::Interface* detector) {

    if (!detector) return;

    // not this class's responsibility to check types, let the holders sort it out
    m_posTimeData.installDetector(detector);
    m_lapData.installDetector(detector);
    m_warnPenData.installDetector(detector);

}



void Processor::Data::DriverState::updateCurrentPosition(const uint8_t currentPosition) {

    m_posTimeData.updateCurrentPosition(m_id, currentPosition);

}



void Processor::Data::DriverState::updateWarningPenalties(const uint8_t totalWarnings,
        const uint8_t trackLimitWarnings, const uint16_t timePenalties,
        const uint8_t stopGoPens, const uint8_t driveThroughPens) {

    m_warnPenData.updateWarningPenalties(m_id, totalWarnings, trackLimitWarnings, timePenalties, stopGoPens, driveThroughPens);

}



void Processor::Data::DriverState::updateStatus(const Participant::Internal::Status status) {

    m_posTimeData.updateStatus(m_id, status);

}


void Processor::Data::DriverState::updateLap(const uint8_t lapID, const Lap::Internal::Type type,
    const Lap::Internal::Status status, const std::vector<Lap::Internal::Time> sectorTimes,
    const float_t lapDistanceRun, const Lap::Internal::Time previousLapTime) {

    m_lapData.updateLap(m_id, lapID, type, status, sectorTimes, lapDistanceRun, previousLapTime);

}