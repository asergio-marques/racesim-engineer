#include "detectors/SectorStateChanged.h"

#include "data/records/DriverRecord.h"
#include "data/records/SessionRecord.h"
#include "data/internal/Sector.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"
#include "packets/event/SectorStateChanged.h"
#include "utilities/Sector.h"




const Processor::Detector::Type Processor::Detector::SectorStateChanged::GetType() const {

    return Processor::Detector::Type::SectorStateChanged;

}



void Processor::Detector::SectorStateChanged::Init(Processor::Data::SessionRecord* sessionRecord,
    std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords) {

    if (m_sessionRecord && m_driverRecords) return;

    Processor::Detector::Interface::doInit(sessionRecord, driverRecords);

}



void Processor::Detector::SectorStateChanged::Deinit() {

    if (!m_sessionRecord || !m_driverRecords) return;

    Processor::Detector::Interface::doDeinit();

}



bool Processor::Detector::SectorStateChanged::checkFastestInSession(Lap::Internal::Sector& finishedSector) {

    if (!m_sessionRecord || !m_sessionRecord->getModifiableState() ||
        (finishedSector.m_performance == Lap::Internal::Performance::FinishedPits) ||
        (finishedSector.m_performance == Lap::Internal::Performance::FinishedInvalid) ||
        (finishedSector.m_performance == Lap::Internal::Performance::FinishedRetired)) return false;

    // If this section that has just finished is indeed the fastest in the session of its kind,
    // then the previous best is required to be revised
    bool isSessionFastest = false;
    const Lap::Internal::Sector revisedSector = m_sessionRecord->getModifiableState()->evaluateCompletedSector(finishedSector, isSessionFastest);
    if (!isSessionFastest) {

        return false;

    }

    auto newBestIt = m_driverRecords->find(finishedSector.getDriverID());
    if (newBestIt == m_driverRecords->end()) {

        return false;

    }

    Packet::Event::SectorStateChanged* newBestSectorPacket = new Packet::Event::SectorStateChanged(
            newBestIt->second->m_info.m_isPlayer,
            newBestIt->second->m_info.m_fullName,
            newBestIt->second->getModifiableState()->posTimeData().getCurrentPosition());
    newBestSectorPacket->m_index = finishedSector.getDriverID();
    newBestSectorPacket->m_lapID = finishedSector.getLapID();
    newBestSectorPacket->m_parentID = finishedSector.getParentID();
    newBestSectorPacket->m_sectorParentOrderID = finishedSector.getParentOrderID();
    newBestSectorPacket->m_isMiniSector = finishedSector.isMiniSector();
    newBestSectorPacket->m_sectorStatus = finishedSector.m_status;
    newBestSectorPacket->m_sectorPerformance = finishedSector.m_performance;
    newBestSectorPacket->m_time = finishedSector.totalTime();
    m_packetsToBeProcessed.push_back(newBestSectorPacket);

    if (Processor::Utility::Sector::validate(revisedSector)) {

        auto oldBestIt = m_driverRecords->find(finishedSector.getDriverID());
        if (oldBestIt != m_driverRecords->end()) {

            Packet::Event::SectorStateChanged* oldBestSectorPacket = new Packet::Event::SectorStateChanged(
                    oldBestIt->second->m_info.m_isPlayer,
                    oldBestIt->second->m_info.m_fullName,
                    oldBestIt->second->getModifiableState()->posTimeData().getCurrentPosition());
            oldBestSectorPacket->m_index = finishedSector.getDriverID();
            oldBestSectorPacket->m_lapID = finishedSector.getLapID();
            oldBestSectorPacket->m_parentID = finishedSector.getParentID();
            oldBestSectorPacket->m_sectorParentOrderID = finishedSector.getParentOrderID();
            oldBestSectorPacket->m_isMiniSector = finishedSector.isMiniSector();
            oldBestSectorPacket->m_sectorStatus = finishedSector.m_status;
            oldBestSectorPacket->m_sectorPerformance = finishedSector.m_performance;
            oldBestSectorPacket->m_time = finishedSector.totalTime();
            m_packetsToBeProcessed.push_back(oldBestSectorPacket);

        }

    }

    return true;

}



void Processor::Detector::SectorStateChanged::addChangedSectorInfo(Lap::Internal::Sector& finishedSector) {

    if (!m_sessionRecord || !m_sessionRecord->getModifiableState() ||
        (finishedSector.m_performance == Lap::Internal::Performance::FinishedPits) ||
        (finishedSector.m_performance == Lap::Internal::Performance::FinishedInvalid) ||
        (finishedSector.m_performance == Lap::Internal::Performance::FinishedRetired)) return;

    auto it = m_driverRecords->find(finishedSector.getDriverID());
    if (it != m_driverRecords->end()) {

        Packet::Event::SectorStateChanged* packet = new Packet::Event::SectorStateChanged(
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