#include "packets/event/RaceStart.h"

#include <list>
#include "data/internal/Session.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"


Packet::Event::RaceStart::RaceStart() :
    Packet::Event::Interface() {



}



const Packet::Event::Type Packet::Event::RaceStart::packetType() const {

    return Packet::Event::Type::RaceStart;

}