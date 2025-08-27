#include "packets/event/TimeTrialStart.h"

#include "data/internal/Session.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



Packet::Event::TimeTrialStart::TimeTrialStart(const uint64_t timestamp) :
    Packet::Event::Interface(timestamp) {



}



const Packet::Event::Type Packet::Event::TimeTrialStart::packetType() const {

    return Packet::Event::Type::TimeTrialStart;

}