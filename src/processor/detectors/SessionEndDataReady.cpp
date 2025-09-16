#include "detectors/SessionEndDataReady.h"

#include "data/records/DriverRecord.h"
#include "data/records/DriverState.h"
#include "data/records/SessionRecord.h"
#include "data/records/SessionState.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"
#include "packets/event/RoundSessionEnd.h"




Processor::Detector::SessionEndDataReady::SessionEndDataReady() :
    Processor::Detector::Interface(),
    m_sentSessionEnd(true) {



}



const Processor::Detector::Type Processor::Detector::SessionEndDataReady::GetType() const {

    return Processor::Detector::Type::SessionEndDataReady;

}



void Processor::Detector::SessionEndDataReady::Init(Processor::Data::SessionRecord* sessionRecord,
                std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords) {

    if (m_sessionRecord && m_driverRecords) return;

    Processor::Detector::Interface::doInit(sessionRecord, driverRecords);

    if (m_sessionRecord && m_driverRecords) {

        m_sentSessionEnd = false;
        if (m_workerThread.joinable()) m_workerThread.join();
        m_workerThread = std::thread(&Processor::Detector::SessionEndDataReady::Exec, this);

    }

}



void Processor::Detector::SessionEndDataReady::Deinit() {

    if (!m_sessionRecord || !m_driverRecords) return;

    Processor::Detector::Interface::doDeinit();

}



void Processor::Detector::SessionEndDataReady::Exec() {

    while (!m_sentSessionEnd && m_sessionRecord && m_driverRecords) {

        bool isAllFinished = !(m_sessionRecord->getModifiableState()->Initialized());

        for (const auto driver : *m_driverRecords) {

            if (driver.second) {

                isAllFinished &= driver.second->Finalized();

            }
            else {
                isAllFinished = false;
                break;
            }

        }
        if (isAllFinished) {

            switch (m_sessionRecord->getSessionSettings().m_sessionType) {

                case Session::Internal::Type::FreePractice:
                case Session::Internal::Type::Qualifying:
                case Session::Internal::Type::Race:
                    BuildRoundSessionEndPacket();
                    break;

                case Session::Internal::Type::TimeTrial:
                    // TODO implement time trial
                    break;

                default:
                    // do nothing
                    break;

            }

            m_sentSessionEnd = true;

        }


        // Thread is executed at 10Hz
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }

}



void Processor::Detector::SessionEndDataReady::BuildRoundSessionEndPacket() {

    Packet::Event::RoundSessionEnd* packet = new Packet::Event::RoundSessionEnd;
    // no information is needed at the moment
    m_packetsToBeProcessed.push_back(packet);

}