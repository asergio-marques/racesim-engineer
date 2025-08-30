#include "packets/internal/TyreSetUsage.h"

#include <cstdint>
#include <vector>
#include "data/internal/Tyre.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



Packet::Internal::TyreSetUsage::Data::Data(const bool hasSetId) :
    m_driverID(UINT8_MAX),
    m_hasSetId(hasSetId),
    m_tyreSetID(UINT8_MAX),
    m_actualTyreCompound(Tyre::Internal::Actual::InvalidUnknown),
    m_visualTyreCompound(Tyre::Internal::Visual::InvalidUnknown),
    m_tyreAgeLaps(UINT8_MAX) {

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