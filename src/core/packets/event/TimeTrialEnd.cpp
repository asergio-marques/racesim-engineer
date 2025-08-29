#include "packets/event/TimeTrialEnd.h"

#include "data/internal/Session.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



Packet::Event::TimeTrialEnd::TimeTrialEnd() :
    Packet::Event::Interface() {



}



const Packet::Event::Type Packet::Event::TimeTrialEnd::packetType() const {

    return Packet::Event::Type::TimeTrialEnd;

}