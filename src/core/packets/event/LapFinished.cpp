#include "packets/event/LapFinished.h"

#include <cstdint>
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



Packet::Event::LapFinished::LapFinished(const bool isPlayer, const std::string fullName, const uint8_t currentPosition) :
    Packet::Event::Interface(isPlayer, fullName, currentPosition),
    m_index(0),
    m_lapTime(),
    m_infoType(Lap::Internal::InfoType::InvalidUnknown) {



}



const Packet::Event::Type Packet::Event::LapFinished::packetType() const {

    return Packet::Event::Type::LapFinished;

}