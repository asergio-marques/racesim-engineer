#include "detectors/LapFinished.h"

#include "data/DriverRecord.h"
#include "data/SessionRecord.h"
#include "data/holders/LapInfo.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"
#include "packets/event/LapFinished.h"



const Processor::Detector::Type Processor::Detector::LapFinished::GetType() const {

    return Processor::Detector::Type::LapFinished;

}



void Processor::Detector::LapFinished::Init(Processor::Data::SessionRecord* sessionRecord,
                std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords) {

    // TODO this will disable graceful closing and reinit once another session is started
    // no need to do anything if we already have the record
    if (m_sessionRecord && m_driverRecords) return;

    Processor::Detector::Interface::doInit(sessionRecord, driverRecords);

}



bool Processor::Detector::LapFinished::checkFastestInSession(const Processor::Data::LapInfo& finishedLap) {

    if (!m_sessionRecord || !m_sessionRecord->getModifiableState()) return false;

    if (m_sessionRecord->getModifiableState()->evaluateCompletedLap(finishedLap)) {

        auto it = m_driverRecords->find(finishedLap.m_driverId);
        if (it != m_driverRecords->end()) {

            Packet::Event::LapFinished* packet = new Packet::Event::LapFinished(
                    it->second->m_info.m_isPlayer,
                    it->second->m_info.m_fullName,
                    it->second->getModifiableState()->posTimeData().getCurrentPosition());
            packet->m_index = finishedLap.m_driverId;
            packet->m_infoType = Lap::Internal::InfoType::FastestLap;
            packet->m_lapTime = finishedLap.m_totalLapTime;
            m_packetsToBeProcessed.push_back(packet);
            return true;

        }

    }
        
    return false;

}



void Processor::Detector::LapFinished::addFinishedLapInfo(const Processor::Data::LapInfo& finishedLap, const Lap::Internal::InfoType infoType) {
    
    if (!m_sessionRecord) return;

    auto it = m_driverRecords->find(finishedLap.m_driverId);
    if (it != m_driverRecords->end()) {

        Packet::Event::LapFinished* packet = new Packet::Event::LapFinished(
            it->second->m_info.m_isPlayer,
            it->second->m_info.m_fullName,
            it->second->getModifiableState()->posTimeData().getCurrentPosition());
        packet->m_index = finishedLap.m_driverId;
        packet->m_infoType = infoType;
        packet->m_lapTime = finishedLap.m_totalLapTime;
        m_packetsToBeProcessed.push_back(packet);

    }

}