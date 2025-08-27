#include "packets/internal/race_types/RaceStandings.h"

#include <cstdint>
#include <vector>
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



Packet::Internal::RaceStandings::Data::Data(const uint8_t driverID, const uint8_t position) :
    m_driverID(driverID),
    m_position(position) {

}



Packet::Internal::RaceStandings::RaceStandings(const uint64_t timestamp) :
    Packet::Internal::Interface(timestamp),
    m_fullStandingsData() {

}



const Packet::Internal::Type Packet::Internal::RaceStandings::packetType() const {

    return Packet::Internal::Type::Standings;

}



void Packet::Internal::RaceStandings::InsertData(const uint8_t driverID, const uint8_t position) {

    m_fullStandingsData.push_back(Packet::Internal::RaceStandings::Data(driverID, position));

}



const std::vector<Packet::Internal::RaceStandings::Data>& Packet::Internal::RaceStandings::GetData() const {

    return m_fullStandingsData;

}