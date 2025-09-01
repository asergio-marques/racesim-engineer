#include "detectors/PenaltyReceived.h"

#include "data/DriverRecord.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"
#include "packets/event/PenaltyReceived.h"



const Processor::Detector::Type Processor::Detector::PenaltyReceived::GetType() const {

    return Processor::Detector::Type::PenaltyReceived;

}



void Processor::Detector::PenaltyReceived::Init(Processor::Data::SessionRecord* sessionRecord,
                std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords) {

    // TODO this will disable graceful closing and reinit once another session is started
    // no need to do anything if we already have the record
    if (m_sessionRecord && m_driverRecords) return;

    Processor::Detector::Interface::doInit(sessionRecord, driverRecords);

}



void Processor::Detector::PenaltyReceived::AddWarnPenChange(const int8_t id, const int8_t diffWarns,
                const int8_t diffTrackLims, const int32_t diffTimePens,
                const int8_t diffStopGo, const int8_t diffDriveThrough) {

    if (!m_driverRecords) return;

    auto it = m_driverRecords->find(id);
    if (it != m_driverRecords->end()) {
        // do nothing for now, I don't know if needed
        /*if (diffWarns != 0) {

            Packet::Internal::PenaltyReceived* packet = new Packet::Internal::PenaltyReceived();
            packet->m_type = Penalty::Internal::Type::Warning;
            packet->m_delta = diffWarns;
            m_packetsToBeProcessed.push_back(packet);

        }*/

        if (diffTrackLims != 0) {

            Packet::Event::PenaltyReceived* packet = new Packet::Event::PenaltyReceived(
                it->second->m_info.m_isPlayer,
                it->second->m_info.m_fullName,
                it->second->getModifiableState()->posTimeData().getCurrentPosition());
            packet->m_type = Penalty::Internal::Type::Warning;
            packet->m_index = id;
            packet->m_delta = diffTrackLims;
            m_packetsToBeProcessed.push_back(packet);

        }

        if (diffTimePens != 0) {

            Packet::Event::PenaltyReceived* packet = new Packet::Event::PenaltyReceived(
                it->second->m_info.m_isPlayer,
                it->second->m_info.m_fullName,
                it->second->getModifiableState()->posTimeData().getCurrentPosition());
            packet->m_type = Penalty::Internal::Type::Time;
            packet->m_index = id;
            packet->m_delta = diffTimePens;
            m_packetsToBeProcessed.push_back(packet);

        }

        if (diffStopGo != 0) {

            Packet::Event::PenaltyReceived* packet = new Packet::Event::PenaltyReceived(
                it->second->m_info.m_isPlayer,
                it->second->m_info.m_fullName,
                it->second->getModifiableState()->posTimeData().getCurrentPosition());
            packet->m_type = Penalty::Internal::Type::StopGo;
            packet->m_index = id;
            packet->m_delta = diffStopGo;
            m_packetsToBeProcessed.push_back(packet);

        }

        if (diffDriveThrough != 0) {

            Packet::Event::PenaltyReceived* packet = new Packet::Event::PenaltyReceived(
                it->second->m_info.m_isPlayer,
                it->second->m_info.m_fullName,
                it->second->getModifiableState()->posTimeData().getCurrentPosition());
            packet->m_type = Penalty::Internal::Type::DriveThrough;
            packet->m_index = id;

            packet->m_delta = diffDriveThrough;
            m_packetsToBeProcessed.push_back(packet);

        }

    }

}