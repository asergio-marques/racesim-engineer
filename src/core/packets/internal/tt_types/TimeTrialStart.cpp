#include "packets/internal/tt_types/TimeTrialStart.h"

#include "data/internal/Session.h"
#include "packets/internal/SoloSessionStart.h"



Packet::Internal::TimeTrialStart::TimeTrialStart(const uint64_t timestamp) :
    Packet::Internal::SoloSessionStart(timestamp, Session::Internal::Type::TimeTrial) {



}