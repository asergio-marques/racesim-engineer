#include "packets/internal/TyreSetUsage.h"

#include <cstdint>
#include <vector>
#include "data/internal/Tyre.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



Packet::Internal::TyreSetUsage::Data::Data() :
    m_driverID(UINT8_MAX),
    m_info() {

}



Packet::Internal::TyreSetUsage::TyreSetUsage(const uint64_t timestamp) :
    Packet::Internal::Interface(timestamp),
    m_fullData() {

}



const Packet::Internal::Type Packet::Internal::TyreSetUsage::packetType() const {

    return Packet::Internal::Type::TyreSetUsage;

}



void Packet::Internal::TyreSetUsage::InsertData(const uint8_t driverID, Tyre::Internal::Data tyreData) {

    Packet::Internal::TyreSetUsage::Data data;
    data.m_driverID = driverID;
    data.m_info = tyreData;

    m_fullData.push_back(data);

}



const std::vector<Packet::Internal::TyreSetUsage::Data>& Packet::Internal::TyreSetUsage::GetData() const {

    return m_fullData;

}