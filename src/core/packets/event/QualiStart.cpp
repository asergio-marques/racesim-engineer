#include "packets/event/QualiStart.h"

#include "data/internal/Session.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



Packet::Event::QualiStart::QualiStart(const uint64_t timestamp, uint8_t carsClassifiedAtEnd) :
    Packet::Event::Interface(timestamp),
    m_carsClassifiedAtEnd(carsClassifiedAtEnd) {



}



const Packet::Event::Type Packet::Event::QualiStart::packetType() const {

    return Packet::Event::Type::QualiStart;

}