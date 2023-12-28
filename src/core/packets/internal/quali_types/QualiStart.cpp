#include "packets/internal/quali_types/QualiStart.h"

#include "packets/internal/SessionStart.h"
#include "data/internal/Session.h"



const Session::Internal::Type Packet::Internal::QualiStart::SessionType() const {

    return Session::Internal::Type::Qualifying;

}