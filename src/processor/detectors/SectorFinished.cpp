#include "detectors/SectorFinished.h"

#include "data/records/DriverRecord.h"
#include "data/records/SessionRecord.h"
#include "data/internal/Sector.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"
#include "packets/event/SectorFinished.h"




const Processor::Detector::Type Processor::Detector::SectorFinished::GetType() const {

    return Processor::Detector::Type::SectorFinished;

}



void Processor::Detector::SectorFinished::Init(Processor::Data::SessionRecord* sessionRecord,
    std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords) {

    if (m_sessionRecord && m_driverRecords) return;

    Processor::Detector::Interface::doInit(sessionRecord, driverRecords);

}



void Processor::Detector::SectorFinished::Deinit() {

    if (!m_sessionRecord || !m_driverRecords) return;

    Processor::Detector::Interface::doDeinit();

}



bool Processor::Detector::SectorFinished::checkFastestInSession(Lap::Internal::Sector& finishedSector) {

    if (!m_sessionRecord || !m_sessionRecord->getModifiableState() ||
        (finishedSector.m_performance == Lap::Internal::Performance::FinishedPits) ||
        (finishedSector.m_performance == Lap::Internal::Performance::FinishedInvalid) ||
        (finishedSector.m_performance == Lap::Internal::Performance::FinishedRetired)) return false;

    if (m_sessionRecord->getModifiableState()->evaluateCompletedSector(finishedSector)) {

        auto it = m_driverRecords->find(finishedSector.getDriverID());
        if (it != m_driverRecords->end()) {

            Packet::Event::SectorFinished* packet = new Packet::Event::SectorFinished(
                    it->second->m_info.m_isPlayer,
                    it->second->m_info.m_fullName,
                    it->second->getModifiableState()->posTimeData().getCurrentPosition());
            packet->m_index = finishedSector.getDriverID();
            packet->m_parentID = finishedSector.getParentID();
            packet->m_sectorParentOrderID = finishedSector.getParentOrderID();
            packet->m_isMiniSector = finishedSector.isMiniSector();
            packet->m_sectorStatus = finishedSector.m_status;
            packet->m_sectorPerformance = finishedSector.m_performance;
            packet->m_time = finishedSector.totalTime();
            m_packetsToBeProcessed.push_back(packet);
            return true;

        }

    }

    return false;

}



void Processor::Detector::SectorFinished::AddFinishedSectorInfo(Lap::Internal::Sector& finishedSector) {

    if (!m_sessionRecord || !m_sessionRecord->getModifiableState() ||
        (finishedSector.m_performance == Lap::Internal::Performance::FinishedPits) ||
        (finishedSector.m_performance == Lap::Internal::Performance::FinishedInvalid) ||
        (finishedSector.m_performance == Lap::Internal::Performance::FinishedRetired)) return;

    auto it = m_driverRecords->find(finishedSector.getDriverID());
    if (it != m_driverRecords->end()) {

        Packet::Event::SectorFinished* packet = new Packet::Event::SectorFinished(
                    it->second->m_info.m_isPlayer,
                    it->second->m_info.m_fullName,
                    it->second->getModifiableState()->posTimeData().getCurrentPosition());
        packet->m_index = finishedSector.getDriverID();
        packet->m_parentID = finishedSector.getParentID();
        packet->m_sectorParentOrderID = finishedSector.getParentOrderID();
        packet->m_isMiniSector = finishedSector.isMiniSector();
        packet->m_sectorStatus = finishedSector.m_status;
        packet->m_sectorPerformance = finishedSector.m_performance;
        packet->m_time = finishedSector.totalTime();
        m_packetsToBeProcessed.push_back(packet);

    }

}