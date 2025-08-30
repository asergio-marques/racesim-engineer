#include "packets/internal/TyreSetUsage.h"

#include <cstdint>
#include <vector>
#include "data/internal/Tyre.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



Packet::Internal::TyreSetUsage::Data::Data(const uint8_t driverID, const uint8_t tyreSetID,
                    const Tyre::Internal::Actual actualTyreCompound, const Tyre::Internal::Visual visualTyreCompound) :
    m_driverID(driverID),
    m_tyreSetID(tyreSetID),
    m_actualTyreCompound(actualTyreCompound),
    m_visualTyreCompound(visualTyreCompound) {

}



Packet::Internal::TyreSetUsage::TyreSetUsage(const uint64_t timestamp) :
    Packet::Internal::Interface(timestamp),
    m_fullData() {

}



const Packet::Internal::Type Packet::Internal::TyreSetUsage::packetType() const {

    return Packet::Internal::Type::TyreSetUsage;

}



void Packet::Internal::TyreSetUsage::InsertData(const Packet::Internal::TyreSetUsage::Data& data) {

    m_fullData.push_back(data);

}



const std::vector<Packet::Internal::TyreSetUsage::Data>& Packet::Internal::TyreSetUsage::GetData() const {

    return m_fullData;

}