#include "detectors/ParticipantStatusChanged.h"

#include <cstdint>
#include <vector>
#include "detectors/Interface.h"
#include "detectors/Type.h"
#include "packets/event/ParticipantStatusChanged.h"



const Processor::Detector::Type Processor::Detector::ParticipantStatusChanged::GetType() const {

    return Processor::Detector::Type::ParticipantStatusChanged;

}



void Processor::Detector::ParticipantStatusChanged::AddStatusChange(const uint8_t id, const Participant::Internal::Status newStatus) {

    Packet::Event::ParticipantStatusChanged* packet = new Packet::Event::ParticipantStatusChanged(0);
    packet->m_index = id;
    packet->m_status = newStatus;
    m_packetsToBeProcessed.push_back(packet);

}