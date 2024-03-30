#include "data/DriverState.h"

#include <cstdint>
#include "detectors/Interface.h"
#include "detectors/Overtake.h"
#include "detectors/Type.h"



Processor::Data::DriverState::DriverState(const uint8_t id, const uint8_t startingPosition) :
    m_id(id),
    m_startingPosition(startingPosition),
    m_currentPosition(startingPosition),
    m_installedOvertakeDetector(nullptr) {




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
            // TODO implement
            break;

        default:
            // shit's fucked
            break;

    }

}



void Processor::Data::DriverState::updateCurrentPosition(const uint8_t currentPosition) {

    // Only add a position change if it actually exists
    if (m_installedOvertakeDetector && (m_currentPosition != currentPosition)) {

        m_installedOvertakeDetector->AddPositionChange(m_id, m_currentPosition, currentPosition);
        m_currentPosition = currentPosition;

    }

}