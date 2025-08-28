#include "packets/internal/GridPosition.h"

#include <cstdint>
#include <vector>
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



Packet::Internal::GridPosition::Data::Data(const uint8_t driverID, const uint8_t position) :
    m_driverID(driverID),
    m_position(position) {

}



Packet::Internal::GridPosition::GridPosition(const uint64_t timestamp) :
    Packet::Internal::Interface(timestamp),
    m_fullGridData() {

}



const Packet::Internal::Type Packet::Internal::GridPosition::packetType() const {

    return Packet::Internal::Type::GridPosition;

}



void Packet::Internal::GridPosition::InsertData(const uint8_t driverID, const uint8_t position) {

    m_fullGridData.push_back(Packet::Internal::GridPosition::Data(driverID, position));

}



const std::vector<Packet::Internal::GridPosition::Data>& Packet::Internal::GridPosition::GetData() const {

    return m_fullGridData;

}