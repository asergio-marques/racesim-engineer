#include "packets/event/PenaltyReceived.h"

#include <cstdint>
#include "data/internal/Penalty.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



Packet::Event::PenaltyReceived::PenaltyReceived(const bool isPlayer, const std::string fullName, const uint8_t currentPosition) :
    Packet::Event::Interface(isPlayer, fullName, currentPosition),
    m_index(0),
    m_type(Penalty::Internal::Type::InvalidUnknown),
    m_delta(0) {



}



const Packet::Event::Type Packet::Event::PenaltyReceived::packetType() const {

    return Packet::Event::Type::PenaltyReceived;

}