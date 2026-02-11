#include "packets/event/PracticeSync.h"

#include <cstdint>
#include <map>
#include <vector>
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"
#include "data/internal/Participant.h"
#include "data/internal/Session.h"
#include "data/internal/Sector.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"




Packet::Event::PracticeSync::PracticeSync() :
    Packet::Event::Interface() {



}



const Packet::Event::Type Packet::Event::PracticeSync::packetType() const {

    return Packet::Event::Type::PracticeSync;

}