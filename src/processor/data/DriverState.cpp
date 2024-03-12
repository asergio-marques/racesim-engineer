#include "data/DriverState.h"

#include <cstdint>
#include <vector>
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



void Processor::Data::DriverState::installDetector(const Processor::Detector::Interface* detector) {

    if (!detector) return;

    switch (detector->GetType()) {

        case Processor::Detector::Type::Overtake:
            m_installedOvertakeDetector = dynamic_cast<const Processor::Detector::Overtake*>(detector);
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

    m_currentPosition = currentPosition;
    if (m_installedOvertakeDetector) {

        //m_installedOvertakeDetector->AddPositionChange(m_id, m_currentPosition);

    }

}


const uint8_t Processor::Data::DriverState::getCurrentPosition() const {

    return m_currentPosition;

}