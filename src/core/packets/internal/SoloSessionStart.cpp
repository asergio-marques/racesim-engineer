#include "packets/internal/SoloSessionStart.h"

#include <cstdint>
#include "packets/internal/SessionStart.h"
#include "data/internal/Session.h"



Packet::Internal::SoloSessionStart::SoloSessionStart(const uint64_t timestamp, const Session::Internal::Type& sessionType) :
    Packet::Internal::SessionStart(timestamp, sessionType) {



}