#include "packets/internal/race_types/RaceStart.h"

#include "packets/internal/SessionStart.h"
#include "data/internal/Session.h"



const Session::Internal::Type Packet::Internal::RaceStart::SessionType() const {

    return Session::Internal::Type::Race;

}