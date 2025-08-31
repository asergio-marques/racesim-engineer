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
    m_isFinished(false),
    m_posTimeData(),
    m_warnPenData() {




}



bool Processor::Data::DriverState::installDetector(Processor::Detector::Interface* detector) {

    bool installed = false;

    if (!detector) return installed;

    // not this class's responsibility to check types, let the holders sort it out
    installed |= m_posTimeData.installDetector(detector);
    installed |= m_lapData.installDetector(detector);
    installed |= m_warnPenData.installDetector(detector);

    return installed;

}



void Processor::Data::DriverState::markAsFinished() {

    m_isFinished = true;

}



void Processor::Data::DriverState::setGridPosition(const uint8_t gridPosition) {

    m_posTimeData.setGridPosition(gridPosition);

}



void Processor::Data::DriverState::setStartingTyreData(const Tyre::Internal::Data tyreData) {

    m_lapData.initialize(m_id, tyreData);

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


bool Processor::Data::DriverState::updateLap(const uint8_t lapID, const Lap::Internal::Type type,
    const Lap::Internal::Status status, const Lap::Internal::Time currentLapTime, const std::vector<Lap::Internal::Time> sectorTimes,
    const float_t lapDistanceRun, const Lap::Internal::Time previousLapTime) {

    // Checking the finished status rather than using the SessionEnd packet solely as source of truth means that in multiplayer sessions
    // the user may not have to wait until the very last packet and may get info before
    const bool driverFinished = m_isFinished || m_posTimeData.isFinishedStatus();
    auto newDriverStatus = m_lapData.updateLap(m_id, lapID, type, status, currentLapTime, sectorTimes, lapDistanceRun, previousLapTime, driverFinished);
    return newDriverStatus;

}



void Processor::Data::DriverState::updateCurrentTyre(const uint8_t driverID, const Tyre::Internal::Data data) {

    m_lapData.updateTyre(driverID, data);

}



const Processor::Data::PositionTimingData& Processor::Data::DriverState::posTimeData() const {

    return m_posTimeData;

}



const Processor::Data::WarningPenaltyData& Processor::Data::DriverState::warnPenData() const {

    return m_warnPenData;

}



const Processor::Data::LapHistoryData& Processor::Data::DriverState::lapData() const {

    return m_lapData;

}