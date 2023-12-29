#include "packets/internal/race_types/RaceStart.h"

#include <list>
#include "data/internal/Session.h"
#include "packets/internal/MPSessionStart.h"



Packet::Internal::RaceStart::RaceStart(uint8_t numLaps) :
    Packet::Internal::MPSessionStart(Session::Internal::Type::Race),
    m_numLaps(numLaps) {



}