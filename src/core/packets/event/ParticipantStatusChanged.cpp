#include "packets/event/ParticipantStatusChanged.h"

#include <cstdint>
#include "data/internal/Participant.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



Packet::Event::ParticipantStatusChanged::ParticipantStatusChanged() :
    Packet::Event::Interface(),
    m_index(0),
    m_status(Participant::Internal::Status::InvalidUnknown) {



}



const Packet::Event::Type Packet::Event::ParticipantStatusChanged::packetType() const {

    return Packet::Event::Type::ParticipantStatusChanged;

}