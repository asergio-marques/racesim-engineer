#include "packets/internal/Standings.h"

#include <cstdint>
#include <vector>
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



Packet::Internal::Standings::Data::Data(const uint8_t driverID, const uint8_t position) :
    m_driverID(driverID),
    m_position(position) {

}



Packet::Internal::Standings::Standings(const uint64_t timestamp) :
    Packet::Internal::Interface(timestamp),
    m_fullStandingsData() {

}



const Packet::Internal::Type Packet::Internal::Standings::packetType() const {

    return Packet::Internal::Type::Standings;

}



void Packet::Internal::Standings::InsertData(const uint8_t driverID, const uint8_t position) {

    m_fullStandingsData.push_back(Packet::Internal::Standings::Data(driverID, position));

}



const std::vector<Packet::Internal::Standings::Data>& Packet::Internal::Standings::GetData() const {

    return m_fullStandingsData;

}