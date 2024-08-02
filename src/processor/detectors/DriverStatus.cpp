#include "detectors/DriverStatus.h"

#include <chrono>
#include <cstdint>
#include <thread>
#include <vector>
#include "detectors/Interface.h"
#include "detectors/Type.h"
#include "packets/internal/multi_use/ParticipantStatusChange.h"



const Processor::Detector::Type Processor::Detector::DriverStatus::GetType() const {

    return Processor::Detector::Type::ParticipantStatus;

}



void Processor::Detector::DriverStatus::AddStatusChange(const uint8_t id, const Participant::Internal::Status newStatus) {

    Packet::Internal::ParticipantStatusChange* packet = new Packet::Internal::ParticipantStatusChange(0);
    packet->m_index = id;
    packet->m_status = newStatus;
    m_packetsToBeProcessed.push_back(packet);

}