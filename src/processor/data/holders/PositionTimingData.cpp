#include "data/holders/PositionTimingData.h"

#include <cstdint>
#include "data/internal/Participant.h"
#include "detectors/ParticipantStatusChanged.h"
#include "detectors/Interface.h"
#include "detectors/Overtake.h"
#include "detectors/SessionStartDataReady.h"
#include "detectors/Type.h"



Processor::Data::PositionTimingData::PositionTimingData(const uint8_t startingPosition) :
    m_isGridPositionSet(false),
    m_gridPosition(0),
    m_currentPosition(startingPosition),
    m_startingPosition(startingPosition),
    m_status(Participant::Internal::Status::InvalidUnknown),
    m_installedSessionStartDetector(nullptr),
    m_installedOvertakeDetector(nullptr),
    m_installedStatusDetector(nullptr) {


}



// Add relevant detectors to then be called when relevant
bool Processor::Data::PositionTimingData::installDetector(Processor::Detector::Interface* detector) {

    if (!detector) return false;

    switch (detector->GetType()) {

        case Processor::Detector::Type::SessionStartDataReady:
            m_installedSessionStartDetector = dynamic_cast<Processor::Detector::SessionStartDataReady*>(detector);
            break;

        case Processor::Detector::Type::Overtake:
            m_installedOvertakeDetector = dynamic_cast<Processor::Detector::Overtake*>(detector);
            return true;

        case Processor::Detector::Type::ParticipantStatusChanged:
            m_installedStatusDetector = dynamic_cast<Processor::Detector::ParticipantStatusChanged*>(detector);
            return true;

        default:
            // do nothing
            return false;

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



void Processor::Data::PositionTimingData::setGridPosition(const uint8_t gridPosition) {

    m_currentPosition = gridPosition;
    m_gridPosition = gridPosition;
    m_isGridPositionSet = true;

    if (m_installedSessionStartDetector) {

        //m_installedSessionStartDetector->RecordParticipant()

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