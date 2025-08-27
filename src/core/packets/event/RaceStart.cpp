#include "packets/event/RaceStart.h"

#include <list>
#include "data/internal/Session.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"


Packet::Event::RaceStart::RaceStart(const uint64_t timestamp, uint8_t numLaps) :
    Packet::Event::Interface(timestamp),
    m_numLaps(numLaps) {



}



const Packet::Event::Type Packet::Event::RaceStart::packetType() const {

    return Packet::Event::Type::RaceStart;

}