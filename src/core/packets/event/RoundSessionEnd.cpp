#include "packets/event/RoundSessionEnd.h"

#include "data/internal/Session.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



Packet::Event::RoundSessionEnd::RoundSessionEnd(const uint64_t timestamp) :
    Packet::Event::Interface(timestamp) {



}



const Packet::Event::Type Packet::Event::RoundSessionEnd::packetType() const {

    return Packet::Event::Type::RoundSessionEnd;

}