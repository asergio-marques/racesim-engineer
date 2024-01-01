#include "packets/internal/SessionStart.h"

#include "data/internal/Session.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



Packet::Internal::SessionStart::SessionStart(const Session::Internal::Type& sessionType) :
    Packet::Internal::Interface(),
    m_sessionType(sessionType),
    m_sessionTrack(Session::Internal::Track::Unknown) {



}



const Packet::Internal::Type Packet::Internal::SessionStart::packetType() const {

    return Packet::Internal::Type::SessionStart;

}