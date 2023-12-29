#include "packets/internal/tt_types/TimeTrialStart.h"

#include "data/internal/Session.h"
#include "packets/internal/SoloSessionStart.h"



Packet::Internal::TimeTrialStart::TimeTrialStart() :
    Packet::Internal::SoloSessionStart(Session::Internal::Type::TimeTrial) {



}