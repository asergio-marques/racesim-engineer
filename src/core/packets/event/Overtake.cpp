#include "packets/event/Overtake.h"

#include <cstdint>
#include <vector>
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



Packet::Event::Overtake::Data::Data(const uint8_t driverID, const uint8_t newPosition, const bool positionUp) :
    m_driverID(driverID),
    m_position(newPosition),
    m_moveUp(positionUp) {

}



Packet::Event::Overtake::Overtake(const uint64_t timestamp) :
    Packet::Event::Interface(timestamp),
    m_fullOvertakeData() {

}



const Packet::Event::Type Packet::Event::Overtake::packetType() const {

    return Packet::Event::Type::Overtake;

}



void Packet::Event::Overtake::InsertData(const uint8_t driverID, const uint8_t newPosition, const bool positionUp) {

    m_fullOvertakeData.push_back(Packet::Event::Overtake::Data(driverID, newPosition, positionUp));

}



const std::vector<Packet::Event::Overtake::Data>& Packet::Event::Overtake::GetData() const {

    return m_fullOvertakeData;

}