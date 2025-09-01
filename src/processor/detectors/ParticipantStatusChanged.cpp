#include "detectors/ParticipantStatusChanged.h"

#include <cstdint>
#include <vector>
#include "detectors/Interface.h"
#include "detectors/Type.h"
#include "packets/event/ParticipantStatusChanged.h"



const Processor::Detector::Type Processor::Detector::ParticipantStatusChanged::GetType() const {

    return Processor::Detector::Type::ParticipantStatusChanged;

}



void Processor::Detector::ParticipantStatusChanged::Init(Processor::Data::SessionRecord* sessionRecord,
                std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords) {

    // TODO this will disable graceful closing and reinit once another session is started
    // no need to do anything if we already have the record
    if (m_sessionRecord && m_driverRecords) return;

    Processor::Detector::Interface::doInit(sessionRecord, driverRecords);

}



void Processor::Detector::ParticipantStatusChanged::AddStatusChange(const uint8_t id, const Participant::Internal::Status newStatus) {

    Packet::Event::ParticipantStatusChanged* packet = new Packet::Event::ParticipantStatusChanged();
    packet->m_index = id;
    packet->m_status = newStatus;
    m_packetsToBeProcessed.push_back(packet);

}