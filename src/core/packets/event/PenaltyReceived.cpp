#include "packets/event/PenaltyReceived.h"

#include <cstdint>
#include "data/internal/Penalty.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



Packet::Event::PenaltyReceived::PenaltyReceived() :
    Packet::Event::Interface(),
    m_index(0),
    m_type(Penalty::Internal::Type::InvalidUnknown),
    m_delta(0) {



}



const Packet::Event::Type Packet::Event::PenaltyReceived::packetType() const {

    return Packet::Event::Type::PenaltyReceived;

}