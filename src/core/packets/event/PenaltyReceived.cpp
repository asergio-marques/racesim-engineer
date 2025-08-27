#include "packets/event/PenaltyReceived.h"

#include <cstdint>
#include "data/internal/Penalty.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



Packet::Event::PenaltyReceived::PenaltyReceived(const uint64_t timestamp) :
    Packet::Event::Interface(timestamp),
    m_index(0),
    m_type(Penalty::Internal::Type::InvalidUnknown),
    m_delta(0) {



}



const Packet::Event::Type Packet::Event::PenaltyReceived::packetType() const {

    return Packet::Event::Type::PenaltyReceived;

}