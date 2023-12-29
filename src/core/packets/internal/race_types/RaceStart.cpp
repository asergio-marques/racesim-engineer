#include "packets/internal/race_types/RaceStart.h"

#include <list>
#include "packets/internal/SessionStart.h"
#include "data/internal/Session.h"



Packet::Internal::RaceStart::RaceStart() :
    m_participants() {



}



const Session::Internal::Type Packet::Internal::RaceStart::SessionType() const {

    return Session::Internal::Type::Race;

}



const std::list<Session::Internal::Participant>& Packet::Internal::RaceStart::getParticipantData() const {

    return m_participants;

}