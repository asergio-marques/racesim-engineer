#include "packets/event/PracticeStart.h"

#include "data/internal/Session.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



Packet::Event::PracticeStart::PracticeStart() :
    Packet::Event::Interface(),
    m_duration(0) {



}



const Packet::Event::Type Packet::Event::PracticeStart::packetType() const {

    return Packet::Event::Type::PracticeStart;

}