#include "packets/event/TimeTrialStart.h"

#include "data/internal/Session.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



Packet::Event::TimeTrialStart::TimeTrialStart() :
    Packet::Event::Interface() {



}



const Packet::Event::Type Packet::Event::TimeTrialStart::packetType() const {

    return Packet::Event::Type::TimeTrialStart;

}