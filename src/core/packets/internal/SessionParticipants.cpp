#include "packets/internal/SessionParticipants.h"

#include <cstdint>
#include <string>
#include <vector>
#include "data/internal/Participant.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



Packet::Internal::SessionParticipants::Data::Data(const uint8_t driverID, const bool isPlayer,
    const std::string fullName, std::string shortName, const Session::Internal::TeamID teamID) :
    m_driverID(driverID),
    m_isPlayer(isPlayer),
    m_fullName(fullName),
    m_shortName(shortName),
    m_teamID(teamID) {

}



Packet::Internal::SessionParticipants::SessionParticipants(const uint64_t timestamp, const uint8_t totalParticipants) :
    Packet::Internal::Interface(timestamp),
    m_totalParticipants(totalParticipants),
    m_fullParticipantData() {



}



const Packet::Internal::Type Packet::Internal::SessionParticipants::packetType() const {

    return Packet::Internal::Type::SessionParticipants;

}



void Packet::Internal::SessionParticipants::InsertData(const uint8_t driverID, const bool isPlayer, const std::string fullName,
                    const std::string shortName, const Session::Internal::TeamID teamID) {

    m_fullParticipantData.push_back(Packet::Internal::SessionParticipants::Data(driverID, isPlayer, fullName, shortName, teamID));

}


const uint8_t Packet::Internal::SessionParticipants::GetTotalParticipants() const {

    return m_totalParticipants;

}



const std::vector<Packet::Internal::SessionParticipants::Data>& Packet::Internal::SessionParticipants::GetData() const {

    return m_fullParticipantData;

}