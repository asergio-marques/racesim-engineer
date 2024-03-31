#include "data/DriverState.h"

#include <cstdint>
#include "data/holders/LapTimeData.h"
#include "data/holders/WarningPenaltyData.h"
#include "data/holders/PositionTimingData.h"
#include "detectors/Interface.h"
#include "detectors/Overtake.h"
#include "detectors/WarningPenalty.h"
#include "detectors/Type.h"



Processor::Data::DriverState::DriverState(const uint8_t id, const uint8_t startingPosition) :
    m_id(id),
    m_posTimeData(startingPosition),
    m_warnPenData(),
    m_installedOvertakeDetector(nullptr),
    m_installedPenWarnDetector(nullptr) {




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

        default:
            // shit's fucked
            break;

    }

}



void Processor::Data::DriverState::updateCurrentPosition(const uint8_t currentPosition) {

    // Only add a position change if it actually exists
    if (m_installedOvertakeDetector && (m_posTimeData.m_currentPosition != currentPosition)) {

        m_installedOvertakeDetector->AddPositionChange(m_id,
            m_posTimeData.m_currentPosition,
            currentPosition);
        m_posTimeData.m_currentPosition = currentPosition;

    }

}