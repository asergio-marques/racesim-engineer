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

    if (!m_driverRecords || !m_sessionRecord) return;
    const auto* sessionState = m_sessionRecord->getModifiableState();
    if (!sessionState) return;

    auto packet = QSharedPointer<Packet::Event::RaceSync>::create();

    Packet::Event::RaceSync::ParticipantData participant;
    for (const auto& recordEntry : *m_driverRecords) {

        const auto driverRecord = recordEntry.second;
        if (!driverRecord) continue;

        const auto* driverState = driverRecord->getModifiableState();
        if (driverState && sessionState) {

            // get basic info
            participant.m_index = driverRecord->m_info.m_driverID;
            participant.m_status = driverState->posTimeData().getStatus();
            participant.m_currentPosition = driverState->posTimeData().getCurrentPosition();

            // get lap info
            const auto lastLap = driverState->lapData().getLapData(driverState->lapData().numLapsAvailable() - 1);
            participant.m_lastLapTime = lastLap->m_totalLapTime;
            if ((sessionState->fastestLap().m_driverId == lastLap->m_driverId) &&
                (sessionState->fastestLap().m_lapId == lastLap->m_lapId)) {

                participant.m_lastLapInfoType = Lap::Internal::InfoType::FastestLap;
                participant.m_bestLapTime = lastLap->m_totalLapTime;
                participant.m_bestLapSessionBest = true;
                
            }
            else if (lastLap->m_lapId == driverState->lapData().fastestLapID()) {

                participant.m_lastLapInfoType = Lap::Internal::InfoType::PersonalBest;
                participant.m_bestLapTime = lastLap->m_totalLapTime;
                participant.m_bestLapSessionBest = false;

            }
            else {


                participant.m_lastLapInfoType = Lap::Internal::InfoType::LatestLap;
                if (auto personalBest = driverState->lapData().getLapData(driverState->lapData().fastestLapID())) {

                    participant.m_bestLapTime = personalBest->m_totalLapTime;
                    participant.m_bestLapSessionBest = false;

                }

            }

            // get tyre stint info
            // TODO
            
            // get penalty info
            // TODO

        }

    }

    packet->m_participants.push_back(participant);


    m_packetsToBeProcessed.push_back(packet);


}