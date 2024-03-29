#include "packets/internal/race_types/Overtake.h"

#include <cstdint>
#include <vector>
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



Packet::Internal::Overtake::Data::Data(const uint8_t driverID, const uint8_t newPosition, const bool positionUp) :
    m_driverID(driverID),
    m_position(newPosition),
    m_moveUp(positionUp) {

}



Packet::Internal::Overtake::Overtake(const uint64_t timestamp) :
    Packet::Internal::Interface(timestamp),
    m_fullOvertakeData(),
    m_isFinalized(false) {

}



const Packet::Internal::Type Packet::Internal::Overtake::packetType() const {

    return Packet::Internal::Type::Overtake;

}



void Packet::Internal::Overtake::Finalize() {

    m_isFinalized = true;

}



void Packet::Internal::Overtake::InsertData(const uint8_t driverID, const uint8_t newPosition, const bool positionUp) {

    if (!m_isFinalized) {

        m_fullOvertakeData.push_back(Packet::Internal::Overtake::Data(driverID, newPosition, positionUp));

    }

}



const std::vector<Packet::Internal::Overtake::Data>& Packet::Internal::Overtake::GetData() const {

    return m_fullOvertakeData;

}