#include "packets/internal/race_types/RaceStart.h"

#include <list>
#include "data/internal/Session.h"
#include "packets/internal/multi_use/MPSessionStart.h"



Packet::Internal::RaceStart::RaceStart(const uint64_t timestamp, uint8_t numLaps) :
    Packet::Internal::MPSessionStart(timestamp, Session::Internal::Type::Race),
    m_numLaps(numLaps) {



}