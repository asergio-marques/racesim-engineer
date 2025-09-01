#include "detectors/TyreChanged.h"

#include "data/DriverRecord.h"
#include "data/internal/TyreData.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"
#include "packets/event/TyreChanged.h"




const Processor::Detector::Type Processor::Detector::TyreChanged::GetType() const {

    return Processor::Detector::Type::TyreChanged;

}



void Processor::Detector::TyreChanged::Init(Processor::Data::SessionRecord* sessionRecord,
                std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords) {

    // TODO this will disable graceful closing and reinit once another session is started
    // no need to do anything if we already have the record
    if (m_sessionRecord && m_driverRecords) return;

    Processor::Detector::Interface::doInit(sessionRecord, driverRecords);

    if (m_sessionRecord && m_driverRecords) {

        m_workerThread = std::thread(&Processor::Detector::TyreChanged::Exec, this);

    }

}



void Processor::Detector::TyreChanged::addTyreChangeInfo(const uint8_t driverID, const Tyre::Internal::Data newTyreData) {

    if (!m_driverRecords) return;

    auto it = m_driverRecords->find(driverID);
    if (it != m_driverRecords->end()) {

        Packet::Event::TyreChanged* packet = new Packet::Event::TyreChanged(
            it->second->m_info.m_isPlayer,
            it->second->m_info.m_fullName,
            it->second->getModifiableState()->posTimeData().getCurrentPosition());
        packet->m_index = driverID;
        packet->m_tyreInfo = newTyreData;
        m_packetsToBeProcessed.push_back(packet);

    }

}