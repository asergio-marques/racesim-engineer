#include "packets/event/TyreChanged.h"

#include <cstdint>
#include "data/internal/TyreData.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"




Packet::Event::TyreChanged::TyreChanged() :
    Packet::Event::Interface(),
    m_index(0),
    m_fullName(""),
    m_isPlayer(false),
    m_position(0),
    m_tyreInfo() {



}



const Packet::Event::Type Packet::Event::TyreChanged::packetType() const {

    return Packet::Event::Type::TyreChanged;

}