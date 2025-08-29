#include "detectors/PenaltyReceived.h"

#include "detectors/Interface.h"
#include "detectors/Type.h"
#include "packets/event/PenaltyReceived.h"



const Processor::Detector::Type Processor::Detector::PenaltyReceived::GetType() const {

    return Processor::Detector::Type::PenaltyReceived;

}



void Processor::Detector::PenaltyReceived::AddWarnPenChange(const int8_t id, const int8_t diffWarns,
                const int8_t diffTrackLims, const int32_t diffTimePens,
                const int8_t diffStopGo, const int8_t diffDriveThrough) {

    // do nothing for now, I don't know if needed
    /*if (diffWarns != 0) {

        Packet::Internal::PenaltyChange* packet = new Packet::Internal::PenaltyChange();
        packet->m_type = Penalty::Internal::Type::Warning;
        packet->m_delta = diffWarns;
        m_packetsToBeProcessed.push_back(packet);

    }*/

    if (diffTrackLims != 0) {

        Packet::Event::PenaltyReceived* packet = new Packet::Event::PenaltyReceived();
        packet->m_type = Penalty::Internal::Type::Warning;
        packet->m_index = id;
        packet->m_delta = diffTrackLims;
        m_packetsToBeProcessed.push_back(packet);

    }

    if (diffTimePens != 0) {

        Packet::Event::PenaltyReceived* packet = new Packet::Event::PenaltyReceived();
        packet->m_type = Penalty::Internal::Type::Time;
        packet->m_index = id;
        packet->m_delta = diffTimePens;
        m_packetsToBeProcessed.push_back(packet);

    }

    if (diffStopGo != 0) {

        Packet::Event::PenaltyReceived* packet = new Packet::Event::PenaltyReceived();
        packet->m_type = Penalty::Internal::Type::StopGo;
        packet->m_index = id;
        packet->m_delta = diffStopGo;
        m_packetsToBeProcessed.push_back(packet);

    }

    if (diffDriveThrough != 0) {

        Packet::Event::PenaltyReceived* packet = new Packet::Event::PenaltyReceived();
        packet->m_type = Penalty::Internal::Type::DriveThrough;
        packet->m_index = id;

        packet->m_delta = diffDriveThrough;
        m_packetsToBeProcessed.push_back(packet);

    }

}