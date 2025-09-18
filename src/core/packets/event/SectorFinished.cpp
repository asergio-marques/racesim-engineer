#include "packets/event/SectorFinished.h"

#include <cstdint>
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"




Packet::Event::SectorFinished::SectorFinished(const bool isPlayer, const std::string fullName, const uint8_t currentPosition) :
    Packet::Event::Interface(isPlayer, fullName, currentPosition),
    m_index(0),
    m_lapTime() {



}



const Packet::Event::Type Packet::Event::SectorFinished::packetType() const {

    return Packet::Event::Type::SectorFinished;

}