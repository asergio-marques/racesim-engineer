#include "detectors/TyreChanged.h"

#include "data/DriverRecord.h"
#include "data/internal/TyreData.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"
#include "packets/event/TyreChanged.h"




const Processor::Detector::Type Processor::Detector::TyreChanged::GetType() const {

    return Processor::Detector::Type::TyreChanged;

}



bool Processor::Detector::TyreChanged::InstallDriverRecords(std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords) {

    if (!driverRecords) return false;

    m_driverRecords = driverRecords;

    return true;

}



void Processor::Detector::TyreChanged::addTyreChangeInfo(const uint8_t driverID, const Tyre::Internal::Data newTyreData) {

    if (!m_installedInDriverRecords || !m_driverRecords) return;

    auto it = m_driverRecords->find(driverID);
    if (it != m_driverRecords->end()) {

        Packet::Event::TyreChanged* packet = new Packet::Event::TyreChanged();
        packet->m_index = driverID;
        packet->m_isPlayer = it->second->m_info.m_isPlayer;
        packet->m_fullName = it->second->m_info.m_fullName;
        packet->m_position = it->second->getModifiableState().posTimeData().getCurrentPosition();
        packet->m_tyreInfo = newTyreData;
        m_packetsToBeProcessed.push_back(packet);

    }

}