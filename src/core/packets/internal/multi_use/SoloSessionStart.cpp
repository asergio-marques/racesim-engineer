#include "packets/internal/multi_use/SoloSessionStart.h"

#include <cstdint>
#include "packets/internal/multi_use/SessionStart.h"
#include "data/internal/Session.h"



Packet::Internal::SoloSessionStart::SoloSessionStart(const uint64_t timestamp, const Session::Internal::Type& sessionType) :
    Packet::Internal::SessionStart(timestamp, sessionType) {



}