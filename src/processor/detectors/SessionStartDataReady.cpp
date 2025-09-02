#include "detectors/SessionStartDataReady.h"

#include "data/DriverRecord.h"
#include "data/DriverState.h"
#include "data/SessionRecord.h"
#include "data/SessionState.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"
#include "packets/event/PracticeStart.h"
#include "packets/event/QualiStart.h"
#include "packets/event/RaceStart.h"
#include "packets/event/TimeTrialStart.h"




Processor::Detector::SessionStartDataReady::SessionStartDataReady() :
    Processor::Detector::Interface(),
    m_sentSessionStart(false) {



}



const Processor::Detector::Type Processor::Detector::SessionStartDataReady::GetType() const {

    return Processor::Detector::Type::SessionStartDataReady;

}



void Processor::Detector::SessionStartDataReady::Init(Processor::Data::SessionRecord* sessionRecord,
                std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords) {

    // TODO this will disable graceful closing and reinit once another session is started
    // no need to do anything if we already have the record
    if (m_sessionRecord && m_driverRecords) return;

    Processor::Detector::Interface::doInit(sessionRecord, driverRecords);

    if (m_sessionRecord && m_driverRecords) {

        m_workerThread = std::thread(&Processor::Detector::SessionStartDataReady::Exec, this);

    }

}



void Processor::Detector::SessionStartDataReady::Exec() {

    while (!m_sentSessionStart) {

        if (m_sessionRecord && m_driverRecords) {

            // TODO prepare event packet
            switch (m_sessionRecord->getSessionSettings().m_sessionType) {
                case Session::Internal::Type::FreePractice:
                    BuildFreePracticeStartPacket();
                    break;

                case Session::Internal::Type::Qualifying:
                    BuildQualiStartPacket();
                    break;

                case Session::Internal::Type::Race:
                    BuildRaceStartPacket();
                    break;

                case Session::Internal::Type::TimeTrial:
                    BuildTimeTrialStartPacket();
                    break;

                default:
                    // do nothing
                    break;
            }

            m_sentSessionStart = true;

        }
        // Thread is executed at 10Hz
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }

}



void Processor::Detector::SessionStartDataReady::BuildFreePracticeStartPacket() {

    // TODO actually implement
    // Packet::Event::PracticeStart* packet = new Packet::Event::PracticeStart();

}



void Processor::Detector::SessionStartDataReady::BuildQualiStartPacket() {

    // TODO actually implement
    // Packet::Event::QualiStart* packet = new Packet::Event::QualiStart();

}



void Processor::Detector::SessionStartDataReady::BuildRaceStartPacket() {

    if (!m_driverRecords) return;

    Packet::Event::RaceStart* packet = new Packet::Event::RaceStart();
    packet->m_trackInfo = m_sessionRecord->getTrackInfo();
    packet->m_settings = m_sessionRecord->getSessionSettings();
    for (const auto& recordEntry : *m_driverRecords) {

        const auto record = recordEntry.second;
        if (record && record->getModifiableState()) {

            Session::Internal::Participant participant;
            participant.m_index = record->m_info.m_driverID;
            participant.m_isPlayer = record->m_info.m_isPlayer;
            participant.m_fullName = record->m_info.m_fullName;
            participant.m_shortName = record->m_info.m_shortName;
            participant.m_teamID = record->m_info.m_teamID;

            const auto state = record->getModifiableState();
            participant.m_startPosition = state->posTimeData().getGridPosition();
            const Processor::Data::LapInfo* lapInfo = state->lapData().getLapData(0);
            if (lapInfo) {

                participant.m_startTyreVisual = lapInfo->m_tyre.m_visualTyre;
                participant.m_startTyreActual = lapInfo->m_tyre.m_actualTyre;
                participant.m_startTyreAge = lapInfo->m_tyre.m_stintLength;

                // makes sense to guard this only if the starting tyre info was initialized properly
                packet->m_participants.push_back(participant);

            }

        }

    }

    m_packetsToBeProcessed.push_back(packet);

}



void Processor::Detector::SessionStartDataReady::BuildTimeTrialStartPacket() {

    // TODO actually implement
    // Packet::Event::TimeTrialStart* packet = new Packet::Event::TimeTrialStart();

}