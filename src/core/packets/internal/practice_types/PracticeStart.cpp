#include "packets/internal/practice_types/PracticeStart.h"

#include <list>
#include "data/internal/Session.h"
#include "packets/internal/MPSessionStart.h"



Packet::Internal::PracticeStart::PracticeStart() :
    Packet::Internal::MPSessionStart(Session::Internal::Type::FreePractice) {



}