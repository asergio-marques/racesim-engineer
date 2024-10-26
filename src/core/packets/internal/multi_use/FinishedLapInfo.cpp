#include "packets/internal/multi_use/FinishedLapInfo.h"

#include <cstdint>
#include <vector>
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



Packet::Internal::FinishedLapInfo::FinishedLapInfo(const uint64_t timestamp) :
    Packet::Internal::Interface(timestamp),
    m_index(0),
    m_lapTime(),
    m_infoType(Lap::Internal::InfoType::InvalidUnknown) {



}



const Packet::Internal::Type Packet::Internal::FinishedLapInfo::packetType() const {

    return Packet::Internal::Type::FinishedLapInfo;

}