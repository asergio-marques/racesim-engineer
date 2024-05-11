#include "packets/internal/multi_use/ParticipantStatusChange.h"

#include <cstdint>
#include "data/internal/Participant.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



Packet::Internal::ParticipantStatusChange::ParticipantStatusChange(const uint64_t timestamp) :
    Packet::Internal::Interface(timestamp),
    m_index(0),
    m_status(Participant::Internal::Status::InvalidUnknown) {



}



const Packet::Internal::Type Packet::Internal::ParticipantStatusChange::packetType() const {

    return Packet::Internal::Type::ParticipantStatusChange;

}