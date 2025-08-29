#include "packets/event/Interface.h"

#include <cstdint>
#include "packets/event/Type.h"



Packet::Event::Interface::Interface() :
    m_processed(false) {

}



const bool Packet::Event::Interface::isProcessed() const {

    return m_processed;

}



void Packet::Event::Interface::markAsProcessed() {

    m_processed = true;

}