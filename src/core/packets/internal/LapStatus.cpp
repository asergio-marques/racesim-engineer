#include "packets/internal/LapStatus.h"

#include <cstdint>
#include <vector>
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



Packet::Internal::LapStatus::LapStatus(const uint64_t timestamp, const uint8_t driverID) :
    Packet::Internal::Interface(timestamp),
    m_driverID(driverID) {



}



const Packet::Internal::Type Packet::Internal::LapStatus::packetType() const {

    return Packet::Internal::Type::LapStatus;

}



void Packet::Internal::LapStatus::InsertData(const Packet::Internal::LapStatus::Data data) {

    m_fullStatusData.push_back(data);

}



const std::vector<Packet::Internal::LapStatus::Data>& Packet::Internal::LapStatus::GetData() const {

    return m_fullStatusData;

}