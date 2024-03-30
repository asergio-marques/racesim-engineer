#include "packets/internal/MPSessionStart.h"

#include <cstdint>
#include <vector>
#include "packets/internal/SessionStart.h"
#include "data/internal/Session.h"



Packet::Internal::MPSessionStart::MPSessionStart(const uint64_t timestamp, const Session::Internal::Type& sessionType) :
    Packet::Internal::SessionStart(timestamp, sessionType),
    m_participants() {



}