#include "packets/event/ParticipantStatusChanged.h"

#include <cstdint>
#include "data/internal/Participant.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



Packet::Event::ParticipantStatusChanged::ParticipantStatusChanged(const uint64_t timestamp) :
    Packet::Event::Interface(timestamp),
    m_index(0),
    m_status(Participant::Internal::Status::InvalidUnknown) {



}



const Packet::Event::Type Packet::Event::ParticipantStatusChanged::packetType() const {

    return Packet::Event::Type::ParticipantStatusChanged;

}