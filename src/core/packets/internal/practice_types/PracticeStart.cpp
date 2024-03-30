#include "packets/internal/practice_types/PracticeStart.h"

#include <list>
#include "data/internal/Session.h"
#include "packets/internal/MPSessionStart.h"



Packet::Internal::PracticeStart::PracticeStart(const uint64_t timestamp) :
    Packet::Internal::MPSessionStart(timestamp, Session::Internal::Type::FreePractice) {



}