#include "packets/event/QualiStart.h"

#include "data/internal/Session.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



Packet::Event::QualiStart::QualiStart(uint8_t carsClassifiedAtEnd) :
    Packet::Event::Interface(),
    m_noActiveParticipants(carsClassifiedAtEnd),
    m_noNextSessionParticipants(carsClassifiedAtEnd),
    m_duration(0) {



}



const Packet::Event::Type Packet::Event::QualiStart::packetType() const {

    return Packet::Event::Type::QualiStart;

}