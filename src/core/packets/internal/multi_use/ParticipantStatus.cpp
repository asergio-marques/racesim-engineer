#include "packets/internal/multi_use/ParticipantStatus.h"

#include <cstdint>
#include <vector>
#include "data/internal/Participant.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



Packet::Internal::ParticipantStatus::Data::Data(const uint8_t driverID,
    const Participant::Internal::Status status) :
    m_driverID(driverID),
    m_status(status) {

}



Packet::Internal::ParticipantStatus::ParticipantStatus(const uint64_t timestamp) :
    Packet::Internal::Interface(timestamp),
    m_fullStatusData() {



}



const Packet::Internal::Type Packet::Internal::ParticipantStatus::packetType() const {

    return Packet::Internal::Type::ParticipantStatus;

}



void Packet::Internal::ParticipantStatus::InsertData(const uint8_t driverID, const Participant::Internal::Status status) {

    m_fullStatusData.push_back(Packet::Internal::ParticipantStatus::Data(driverID, status));

}



const std::vector<Packet::Internal::ParticipantStatus::Data>& Packet::Internal::ParticipantStatus::GetData() const {

    return m_fullStatusData;

}