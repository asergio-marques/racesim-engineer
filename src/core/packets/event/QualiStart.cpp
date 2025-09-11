#include "packets/event/QualiStart.h"

#include "data/internal/Session.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



Packet::Event::QualiStart::QualiStart() :
    Packet::Event::Interface() {



}



const Packet::Event::Type Packet::Event::QualiStart::packetType() const {

    return Packet::Event::Type::QualiStart;

}