#include "packets/internal/multi_use/MPSessionStart.h"

#include <cstdint>
#include <vector>
#include "packets/internal/multi_use/SessionStart.h"
#include "data/internal/Session.h"



Packet::Internal::MPSessionStart::MPSessionStart(const uint64_t timestamp, const Session::Internal::Type& sessionType) :
    Packet::Internal::SessionStart(timestamp, sessionType),
    m_participants() {



}