#include "detectors/InfoSynchronizer.h"

#include <chrono>
#include <cstdint>
#include <thread>
#include <vector>
#include <QSharedPointer>
#include "data/records/DriverRecord.h"
#include "data/records/DriverState.h"
#include "data/records/SessionRecord.h"
#include "data/records/SessionState.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"
#include "packets/event/PracticeSync.h"
#include "packets/event/QualiSync.h"
#include "packets/event/RaceSync.h"
#include "packets/event/TimeTrialStart.h"



const Processor::Detector::Type Processor::Detector::InfoSynchronizer::GetType() const {

    return Processor::Detector::Type::InfoSynchronizer;

}



void Processor::Detector::InfoSynchronizer::Init(Processor::Data::SessionRecord* sessionRecord,
                std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords) {

    Processor::Detector::Interface::doInit(sessionRecord, driverRecords);

    if (m_sessionRecord && m_driverRecords) {

        if (m_workerThread.joinable()) m_workerThread.join();
        m_workerThread = std::thread(&Processor::Detector::InfoSynchronizer::Exec, this);

    }

}



void Processor::Detector::InfoSynchronizer::Deinit() {

    if (!m_sessionRecord || !m_driverRecords) return;

    Processor::Detector::Interface::doDeinit();

}



void Processor::Detector::InfoSynchronizer::Exec() {

    while (m_sessionRecord && m_driverRecords) {

        switch (m_sessionRecord->getSessionSettings().m_sessionType) {
            case Session::Internal::Type::FreePractice:
                BuildPracticeSyncPacket();
                break;

            case Session::Internal::Type::Qualifying:
                BuildQualiSyncPacket();
                break;

            case Session::Internal::Type::Race:
                BuildRaceSyncPacket();
                break;

            default:
                // Time trial does not require a sync
                // do nothing
                break;
        }

        // Data sync is only meant to happen once every 10 seconds, to minimize load
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));

    }

}



void Processor::Detector::InfoSynchronizer::BuildPracticeSyncPacket() {



}



void Processor::Detector::InfoSynchronizer::BuildQualiSyncPacket() {



}



void Processor::Detector::InfoSynchronizer::BuildRaceSyncPacket() {

    if (!m_driverRecords) return;

    auto packet = QSharedPointer<Packet::Event::RaceSync>::create();

    Packet::Event::RaceSync::ParticipantData participant;
    for (const auto& recordEntry : *m_driverRecords) {

        const auto record = recordEntry.second;
        const auto* state = record->getModifiableState();
        if (record && state) {

            participant.m_index = record->m_info.m_driverID;
            participant.m_status = state->posTimeData().getStatus();
            participant.m_currentPosition = state->posTimeData().getCurrentPosition();
            // TODO rest

        }

    }

    packet->m_participants.push_back(participant);


    m_packetsToBeProcessed.push_back(packet);


}