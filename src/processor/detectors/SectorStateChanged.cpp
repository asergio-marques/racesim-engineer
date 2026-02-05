#include "detectors/SectorStateChanged.h"

#include <QSharedPointer>
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
        (finishedSector.m_performance == Lap::Internal::Performance::FinishedPitIn) ||
        (finishedSector.m_performance == Lap::Internal::Performance::FinishedPitOut) ||
        (finishedSector.m_performance == Lap::Internal::Performance::FinishedInvalid) ||
        (finishedSector.m_performance == Lap::Internal::Performance::FinishedRetired) ||
        (finishedSector.m_performance == Lap::Internal::Performance::InvalidUnknown)) return false;

    // If this section that has just finished is indeed the fastest in the session of its kind,
    // then the previous best is required to be revised
    bool isSessionFastest = false;
    Lap::Internal::Sector revisedSector = m_sessionRecord->getModifiableState()->evaluateCompletedSector(finishedSector, isSessionFastest);
    if (!isSessionFastest) {

        return false;

    }

    auto newBestIt = m_driverRecords->find(finishedSector.getDriverID());
    if (newBestIt == m_driverRecords->end()) {

        return false;

    }

    auto newBestSectorPacket = QSharedPointer<Packet::Event::SectorStateChanged>::create(
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

    if (Processor::Utility::Sector::validate(revisedSector) && revisedSector.totalTime().valid()) {

        auto oldBestIt = m_driverRecords->find(revisedSector.getDriverID());
        if (oldBestIt != m_driverRecords->end()) {

            revisedSector.m_performance = Lap::Internal::Performance::FinishedPersonalBest;

            auto oldBestSectorPacket = QSharedPointer<Packet::Event::SectorStateChanged>::create(
                    oldBestIt->second->m_info.m_isPlayer,
                    oldBestIt->second->m_info.m_fullName,
                    oldBestIt->second->getModifiableState()->posTimeData().getCurrentPosition());
            oldBestSectorPacket->m_index = revisedSector.getDriverID();
            oldBestSectorPacket->m_lapID = revisedSector.getLapID();
            oldBestSectorPacket->m_parentID = revisedSector.getParentID();
            oldBestSectorPacket->m_sectorParentOrderID = revisedSector.getParentOrderID();
            oldBestSectorPacket->m_isMiniSector = revisedSector.isMiniSector();
            oldBestSectorPacket->m_sectorStatus = revisedSector.m_status;
            oldBestSectorPacket->m_sectorPerformance = revisedSector.m_performance;
            oldBestSectorPacket->m_time = revisedSector.totalTime();
            m_packetsToBeProcessed.push_back(oldBestSectorPacket);

        }

    }

    return true;

}



bool Processor::Detector::SectorStateChanged::checkFastestInSession(Lap::Internal::SimpleSector& finishedSector) {

    if (!m_sessionRecord || !m_sessionRecord->getModifiableState() ||
        (finishedSector.m_performance == Lap::Internal::Performance::FinishedPitIn) ||
        (finishedSector.m_performance == Lap::Internal::Performance::FinishedPitOut) ||
        (finishedSector.m_performance == Lap::Internal::Performance::FinishedInvalid) ||
        (finishedSector.m_performance == Lap::Internal::Performance::FinishedRetired) ||
        (finishedSector.m_performance == Lap::Internal::Performance::InvalidUnknown)) return false;

    // If this section that has just finished is indeed the fastest in the session of its kind,
    // then the previous best is required to be revised
    bool isSessionFastest = false;
    Lap::Internal::SimpleSector revisedSector = m_sessionRecord->getModifiableState()->evaluateCompletedSector(finishedSector, isSessionFastest);
    if (!isSessionFastest) {

        return false;

    }

    auto newBestIt = m_driverRecords->find(finishedSector.getDriverID());
    if (newBestIt == m_driverRecords->end()) {

        return false;

    }

    auto newBestSectorPacket = QSharedPointer<Packet::Event::SectorStateChanged>::create(
            newBestIt->second->m_info.m_isPlayer,
            newBestIt->second->m_info.m_fullName,
            newBestIt->second->getModifiableState()->posTimeData().getCurrentPosition());
    newBestSectorPacket->m_index = finishedSector.getDriverID();
    newBestSectorPacket->m_lapID = finishedSector.getLapID();
    newBestSectorPacket->m_parentID = 0;
    newBestSectorPacket->m_sectorParentOrderID = finishedSector.getSectorID();
    newBestSectorPacket->m_isMiniSector = false;
    newBestSectorPacket->m_sectorStatus = finishedSector.m_status;
    newBestSectorPacket->m_sectorPerformance = finishedSector.m_performance;
    newBestSectorPacket->m_time = finishedSector.m_time;
    m_packetsToBeProcessed.push_back(newBestSectorPacket);

    if (Processor::Utility::Sector::validate(revisedSector) && revisedSector.m_time.valid()) {

        auto oldBestIt = m_driverRecords->find(revisedSector.getDriverID());
        if (oldBestIt != m_driverRecords->end()) {

            revisedSector.m_performance = Lap::Internal::Performance::FinishedPersonalBest;

            auto oldBestSectorPacket = QSharedPointer<Packet::Event::SectorStateChanged>::create(
                    oldBestIt->second->m_info.m_isPlayer,
                    oldBestIt->second->m_info.m_fullName,
                    oldBestIt->second->getModifiableState()->posTimeData().getCurrentPosition());
            oldBestSectorPacket->m_index = revisedSector.getDriverID();
            oldBestSectorPacket->m_lapID = revisedSector.getLapID();
            oldBestSectorPacket->m_parentID = 0;
            oldBestSectorPacket->m_sectorParentOrderID = revisedSector.getSectorID();
            oldBestSectorPacket->m_isMiniSector = false;
            oldBestSectorPacket->m_sectorStatus = revisedSector.m_status;
            oldBestSectorPacket->m_sectorPerformance = revisedSector.m_performance;
            oldBestSectorPacket->m_time = revisedSector.m_time;
            m_packetsToBeProcessed.push_back(oldBestSectorPacket);

        }

    }

    return true;

}



void Processor::Detector::SectorStateChanged::addChangedSectorInfo(Lap::Internal::Sector& changedSector) {

    if (!m_sessionRecord || !m_sessionRecord->getModifiableState() ||
        (changedSector.m_performance == Lap::Internal::Performance::InvalidUnknown)) return;

    auto it = m_driverRecords->find(changedSector.getDriverID());
    if (it != m_driverRecords->end()) {

        auto packet = QSharedPointer<Packet::Event::SectorStateChanged>::create(
                    it->second->m_info.m_isPlayer,
                    it->second->m_info.m_fullName,
                    it->second->getModifiableState()->posTimeData().getCurrentPosition());
        packet->m_index = changedSector.getDriverID();
        packet->m_lapID = changedSector.getLapID();
        packet->m_parentID = changedSector.getParentID();
        packet->m_sectorParentOrderID = changedSector.getParentOrderID();
        packet->m_isMiniSector = changedSector.isMiniSector();
        packet->m_sectorStatus = changedSector.m_status;
        packet->m_sectorPerformance = changedSector.m_performance;
        packet->m_time = changedSector.totalTime();
        m_packetsToBeProcessed.push_back(packet);

    }

}



void Processor::Detector::SectorStateChanged::addChangedSectorInfo(Lap::Internal::SimpleSector& changedSector) {

    if (!m_sessionRecord || !m_sessionRecord->getModifiableState() ||
        (changedSector.m_performance == Lap::Internal::Performance::InvalidUnknown)) return;

    auto it = m_driverRecords->find(changedSector.getDriverID());
    if (it != m_driverRecords->end()) {

        auto packet = QSharedPointer<Packet::Event::SectorStateChanged>::create(
                    it->second->m_info.m_isPlayer,
                    it->second->m_info.m_fullName,
                    it->second->getModifiableState()->posTimeData().getCurrentPosition());
        packet->m_index = changedSector.getDriverID();
        packet->m_lapID = changedSector.getLapID();
        packet->m_parentID = 0;
        packet->m_sectorParentOrderID = changedSector.getSectorID();
        packet->m_isMiniSector = false;
        packet->m_sectorStatus = changedSector.m_status;
        packet->m_sectorPerformance = changedSector.m_performance;
        packet->m_time = changedSector.m_time;
        m_packetsToBeProcessed.push_back(packet);

    }

}