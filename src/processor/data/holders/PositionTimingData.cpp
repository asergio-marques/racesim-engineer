#include "data/holders/PositionTimingData.h"

#include <cstdint>
#include "data/internal/Participant.h"
#include "detectors/DriverStatus.h"
#include "detectors/Interface.h"
#include "detectors/Overtake.h"
#include "detectors/Type.h"



Processor::Data::PositionTimingData::PositionTimingData(const uint8_t startingPosition) :
    m_currentPosition(startingPosition),
    m_startingPosition(startingPosition),
    m_status(Participant::Internal::Status::InvalidUnknown),
    m_installedOvertakeDetector(),
    m_installedStatusDetector() {


}



// Add relevant detectors to then be called when relevant
void Processor::Data::PositionTimingData::installDetector(Processor::Detector::Interface* detector) {

    if (!detector) return;

    switch (detector->GetType()) {

        case Processor::Detector::Type::Overtake:
            m_installedOvertakeDetector = dynamic_cast<Processor::Detector::Overtake*>(detector);
            break;

        case Processor::Detector::Type::ParticipantStatus:
            m_installedStatusDetector = dynamic_cast<Processor::Detector::DriverStatus*>(detector);
            break;

        default:
            // do nothing
            break;

    }

}



void Processor::Data::PositionTimingData::updateStatus(const uint8_t id, const Participant::Internal::Status status) {

    if (m_status != status &&
        m_status != Participant::Internal::Status::DNF &&
        m_status != Participant::Internal::Status::DSQ &&
        m_status != Participant::Internal::Status::FinishedSession) {

        // Update information and feed to detector
        m_status = status;
        if (m_installedStatusDetector) {

            m_installedStatusDetector->AddStatusChange(id, status);

        }

    }

}



void Processor::Data::PositionTimingData::updateCurrentPosition(const uint8_t id, const uint8_t currentPosition) {

    // Only add a position change if it actually exists
    if (m_currentPosition != currentPosition) {

        if (m_installedOvertakeDetector) {

            m_installedOvertakeDetector->AddPositionChange(id, m_currentPosition, currentPosition);

        }

        m_currentPosition = currentPosition;

    }

}



const bool Processor::Data::PositionTimingData::isFinishedStatus() const {

    return m_status == Participant::Internal::Status::FinishedSession ||
        m_status == Participant::Internal::Status::DSQ ||
        m_status == Participant::Internal::Status::DNF;

}