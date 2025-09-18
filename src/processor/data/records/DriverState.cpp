#include "data/records/DriverState.h"

#include <cstdint>
#include <map>
#include <vector>
#include "data/records/DriverRecord.h"
#include "data/holders/LapInfo.h"
#include "data/holders/PositionTimingData.h"
#include "data/holders/TrackData.h"
#include "data/holders/WarningPenaltyData.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"



Processor::Data::DriverState::DriverState(const Processor::Data::DriverRecord* const parent,
    const uint8_t startingPosition, const Processor::Data::TrackData& trackData) :
    m_parentRecord(parent),
    m_posTimeData(),
    m_warnPenData(),
    m_lapData(),
    m_sectorData(false, trackData),
    m_miniSectorData(true, trackData) {




}



void Processor::Data::DriverState::finalize(const uint8_t id, const uint8_t position,
    const uint8_t numLaps, const Lap::Internal::Time sessionTime) {

    m_lapData.completeData(id, numLaps, sessionTime);
    // TODO investigate this better because it doesn't look like it's working perfectly
    // m_posTimeData.updateCurrentPosition(id, position);
    m_posTimeData.updateStatus(id, Participant::Internal::Status::FinishedSession);

}



bool Processor::Data::DriverState::installDetector(Processor::Detector::Interface* detector) {

    bool installed = false;

    if (!detector) return installed;

    // not this class's responsibility to check types, let the holders sort it out
    installed |= m_posTimeData.installDetector(detector);
    installed |= m_lapData.installDetector(detector);
    installed |= m_warnPenData.installDetector(detector);
    installed |= m_sectorData.installDetector(detector);
    installed |= m_miniSectorData.installDetector(detector);

    return installed;

}



void Processor::Data::DriverState::setGridPosition(const uint8_t gridPosition) {

    m_posTimeData.setGridPosition(gridPosition);

}



void Processor::Data::DriverState::setStartingTyreData(const Tyre::Internal::Data tyreData) {

    m_lapData.initialize(m_parentRecord->m_info.m_driverID, tyreData);

}



void Processor::Data::DriverState::updateCurrentPosition(const uint8_t currentPosition) {

    m_posTimeData.updateCurrentPosition(m_parentRecord->m_info.m_driverID, currentPosition);

}



void Processor::Data::DriverState::updateWarningPenalties(const uint8_t totalWarnings,
        const uint8_t trackLimitWarnings, const uint16_t timePenalties,
        const uint8_t stopGoPens, const uint8_t driveThroughPens) {

    m_warnPenData.updateWarningPenalties(m_parentRecord->m_info.m_driverID, totalWarnings, trackLimitWarnings, timePenalties, stopGoPens, driveThroughPens);

}



void Processor::Data::DriverState::updateStatus(const Participant::Internal::Status status) {

    m_posTimeData.updateStatus(m_parentRecord->m_info.m_driverID, status);

}


void Processor::Data::DriverState::updateLap(const uint8_t lapID, const Lap::Internal::Status status,
    const Lap::Internal::Time currentLapTime, const std::vector<Lap::Internal::Time> sectorTimes,
    const float_t lapDistanceRun, const bool isValid, const Lap::Internal::Time previousLapTime) {

    // Checking the finished status rather than using the SessionEnd packet solely as source of truth means that in multiplayer sessions
    // the user may not have to wait until the very last packet and may get info before
    m_lapData.updateLap(m_parentRecord->m_info.m_driverID, lapID, status,
        currentLapTime, sectorTimes, lapDistanceRun, previousLapTime, m_posTimeData.getStatus());
    m_sectorData.update(m_parentRecord->m_info.m_driverID, lapDistanceRun,
        sectorTimes, previousLapTime, status, isValid);
    m_miniSectorData.update(m_parentRecord->m_info.m_driverID, lapDistanceRun,
        currentLapTime, previousLapTime, status, isValid);

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