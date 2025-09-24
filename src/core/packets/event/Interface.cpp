#include "packets/event/Interface.h"

#include <cstdint>
#include <iostream>
#include "packets/event/Type.h"



Packet::Event::Interface::Interface() :
    m_isPlayer(false),
    m_currentPosition(0),
    m_fullName("") {

}



Packet::Event::Interface::Interface(const bool isPlayer, const std::string fullName, const uint8_t currentPosition) :
    m_isPlayer(isPlayer),
    m_currentPosition(currentPosition),
    m_fullName(fullName) {

}



Packet::Event::Interface::~Interface() {

    std::cout << "Event packet was destroyed" << std::endl;

}