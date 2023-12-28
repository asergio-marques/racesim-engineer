#include "packets/internal/practice_types/PracticeStart.h"

#include "packets/internal/SessionStart.h"
#include "data/internal/Session.h"



const Session::Internal::Type Packet::Internal::PracticeStart::SessionType() const {

    return Session::Internal::Type::FreePractice;

}