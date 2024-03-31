#include "packets/internal/multi_use/PenaltyServed.h"

#include <cstdint>
#include "data/internal/Penalty.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



Packet::Internal::PenaltyServed::PenaltyServed(const uint64_t timestamp) :
    Packet::Internal::Interface(timestamp),
    m_index(0),
    m_timeLength(0),
    m_type(Penalty::Internal::Type::InvalidUnknown) {



}



const Packet::Internal::Type Packet::Internal::PenaltyServed::packetType() const {

    return Packet::Internal::Type::PenaltyServed;

}