#include "packets/internal/race_types/PenaltyStatus.h"

#include <cstdint>
#include <vector>
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



Packet::Internal::PenaltyStatus::Data::Data(const uint8_t driverID, const uint8_t totalWarnings,
                    const uint8_t trackLimitWarnings, const uint16_t timePenalties,
                    const uint8_t stopGoPens, const uint8_t driveThroughPens) :
    m_driverID(driverID),
    m_totalWarns(totalWarnings),
    m_numTrackLimits(trackLimitWarnings),
    m_timePenMS(timePenalties),
    m_numStopGo(stopGoPens),
    m_numDriveThrough(driveThroughPens) {

}



Packet::Internal::PenaltyStatus::PenaltyStatus(const uint64_t timestamp) :
    Packet::Internal::Interface(timestamp),
    m_fullPenaltyData() {

}



const Packet::Internal::Type Packet::Internal::PenaltyStatus::packetType() const {

    return Packet::Internal::Type::PenaltyStatus;

}



void Packet::Internal::PenaltyStatus::InsertData(const uint8_t driverID, const uint8_t totalWarnings,
                    const uint8_t trackLimitWarnings, const uint16_t timePenalties,
                    const uint8_t stopGoPens, const uint8_t driveThroughPens) {

    m_fullPenaltyData.push_back(Packet::Internal::PenaltyStatus::Data(driverID,
        totalWarnings,
        trackLimitWarnings,
        timePenalties,
        stopGoPens,
        driveThroughPens));

}



const std::vector<Packet::Internal::PenaltyStatus::Data>& Packet::Internal::PenaltyStatus::GetData() const {

    return m_fullPenaltyData;

}