#include "packets/internal/SessionParticipants.h"

#include <cstdint>
#include <string>
#include <vector>
#include "data/internal/Participant.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"




Packet::Internal::SessionParticipants::SessionParticipants(const uint64_t timestamp, const uint8_t totalParticipants) :
    Packet::Internal::Interface(timestamp),
    m_totalParticipants(totalParticipants),
    m_fullParticipantData() {



}



const Packet::Internal::Type Packet::Internal::SessionParticipants::packetType() const {

    return Packet::Internal::Type::SessionParticipants;

}



void Packet::Internal::SessionParticipants::InsertData(const Session::Internal::Participant input) {

    m_fullParticipantData.push_back(input);

}


const uint8_t Packet::Internal::SessionParticipants::GetTotalParticipants() const {

    return m_totalParticipants;

}



const std::vector<Session::Internal::Participant>& Packet::Internal::SessionParticipants::GetData() const {

    return m_fullParticipantData;

}