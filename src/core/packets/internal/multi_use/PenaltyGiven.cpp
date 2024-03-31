#include "packets/internal/multi_use/PenaltyGiven.h"

#include <cstdint>
#include "data/internal/Penalty.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



Packet::Internal::PenaltyGiven::PenaltyGiven(const uint64_t timestamp) :
    Packet::Internal::Interface(timestamp),
    m_index(0),
    m_type(Penalty::Internal::Type::InvalidUnknown),
    m_reasonforPenalty(Penalty::Internal::Reason::InvalidUnknown),
    m_timeLength(0) {



}



const Packet::Internal::Type Packet::Internal::PenaltyGiven::packetType() const {

    return Packet::Internal::Type::PenaltyGiven;

}