#include "packets/event/TimeTrialEnd.h"

#include "data/internal/Session.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



Packet::Event::TimeTrialEnd::TimeTrialEnd(const uint64_t timestamp) :
    Packet::Event::Interface(timestamp) {



}



const Packet::Event::Type Packet::Event::TimeTrialEnd::packetType() const {

    return Packet::Event::Type::TimeTrialEnd;

}