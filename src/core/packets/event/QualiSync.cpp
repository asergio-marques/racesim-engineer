#include "packets/event/QualiSync.h"

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




Packet::Event::QualiSync::QualiSync() :
    Packet::Event::Interface() {



}



const Packet::Event::Type Packet::Event::QualiSync::packetType() const {

    return Packet::Event::Type::QualiSync;

}