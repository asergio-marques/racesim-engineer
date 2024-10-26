#include "packets/internal/multi_use/SessionStart.h"

#include "data/internal/Session.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



Packet::Internal::SessionStart::SessionStart(const uint64_t timestamp, const Session::Internal::Type& sessionType) :
    Packet::Internal::Interface(timestamp),
    m_sessionType(sessionType),
    m_sessionTrack(Session::Internal::Track::Unknown),
    m_lapDistanceTotal(0.0f),
    m_sector1Distance(0.0f),
    m_sector2Distance(0.0f),
    m_sector3Distance(0.0f) {



}



const Packet::Internal::Type Packet::Internal::SessionStart::packetType() const {

    return Packet::Internal::Type::SessionStart;

}