#include "packets/event/Interface.h"

#include <cstdint>
#include "packets/event/Type.h"



Packet::Event::Interface::Interface() :
    m_processed(false),
    m_isPlayer(false),
    m_currentPosition(0),
    m_fullName("") {

}



Packet::Event::Interface::Interface(const bool isPlayer, const std::string fullName, const uint8_t currentPosition) :
    m_processed(false),
    m_isPlayer(isPlayer),
    m_currentPosition(currentPosition),
    m_fullName(fullName) {

}



const bool Packet::Event::Interface::isProcessed() const {

    return m_processed;

}



void Packet::Event::Interface::markAsProcessed() {

    m_processed = true;

}