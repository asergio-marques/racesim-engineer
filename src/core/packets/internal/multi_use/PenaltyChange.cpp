#include "packets/internal/multi_use/PenaltyChange.h"

#include <cstdint>
#include "data/internal/Penalty.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



Packet::Internal::PenaltyChange::PenaltyChange(const uint64_t timestamp) :
    Packet::Internal::Interface(timestamp),
    m_index(0),
    m_type(Penalty::Internal::Type::InvalidUnknown),
    m_delta(0) {



}



const Packet::Internal::Type Packet::Internal::PenaltyChange::packetType() const {

    return Packet::Internal::Type::PenaltyChange;

}