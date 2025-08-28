#include "packets/event/PracticeStart.h"

#include "data/internal/Session.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



Packet::Event::PracticeStart::PracticeStart(const uint64_t timestamp) :
    Packet::Event::Interface(timestamp),
    m_duration(0) {



}



const Packet::Event::Type Packet::Event::PracticeStart::packetType() const {

    return Packet::Event::Type::PracticeStart;

}