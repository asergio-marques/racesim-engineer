#include "packets/internal/tt_types/TimeTrialStart.h"

#include "packets/internal/SessionStart.h"
#include "data/internal/Session.h"



const Session::Internal::Type Packet::Internal::TimeTrialStart::SessionType() const {

    return Session::Internal::Type::TimeTrial;

}