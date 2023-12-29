#include "packets/internal/SessionStart.h"

#include "packets/internal/Interface.h"
#include "data/internal/Session.h"



Packet::Internal::SessionStart::SessionStart(const Session::Internal::Type& sessionType) :
    Packet::Internal::Interface(),
    m_sessionType(sessionType),
    m_sessionTrack(Session::Internal::Track::Unknown) {



}