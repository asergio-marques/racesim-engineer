#include "packets/internal/FinalResult.h"

#include <cstdint>
#include <vector>
#include "data/internal/LapTime.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



Packet::Internal::FinalResult::Data::Data(const uint8_t driverID, const uint8_t position,
    const uint8_t numLaps, const uint32_t sessionTime, const uint32_t bestLap) :
    m_driverID(driverID),
    m_position(position),
    m_numLaps(numLaps),
    m_sessionTime(sessionTime),
    m_bestLap(bestLap) {

}



Packet::Internal::FinalResult::FinalResult(const uint64_t timestamp) :
    Packet::Internal::Interface(timestamp),
    m_participantEndData() {

}



const Packet::Internal::Type Packet::Internal::FinalResult::packetType() const {

    return Packet::Internal::Type::FinalResult;

}



void Packet::Internal::FinalResult::InsertData(const uint8_t driverID, const uint8_t position,
    const uint8_t numLaps, const uint32_t sessionTime, const uint32_t bestLap) {

    m_participantEndData.push_back(Packet::Internal::FinalResult::Data(driverID, position, numLaps, sessionTime, bestLap));

}



const std::vector<Packet::Internal::FinalResult::Data>& Packet::Internal::FinalResult::GetData() const {

    return m_participantEndData;

}