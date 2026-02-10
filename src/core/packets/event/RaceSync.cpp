#include "packets/event/RaceSync.h"

#include <vector>
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"
#include "data/internal/Participant.h"
#include "data/internal/TyreData.h"
#include "data/internal/Session.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"




Packet::Event::RaceSync::RaceSync() :
    Packet::Event::Interface() {



}



const Packet::Event::Type Packet::Event::RaceSync::packetType() const {

    return Packet::Event::Type::RaceSync;

}