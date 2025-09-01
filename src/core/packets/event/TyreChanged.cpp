#include "packets/event/TyreChanged.h"

#include <cstdint>
#include "data/internal/TyreData.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"




Packet::Event::TyreChanged::TyreChanged(const bool isPlayer, const std::string fullName, const uint8_t currentPosition) :
    Packet::Event::Interface(isPlayer, fullName, currentPosition),
    m_index(0),
    m_tyreInfo() {



}



const Packet::Event::Type Packet::Event::TyreChanged::packetType() const {

    return Packet::Event::Type::TyreChanged;

}