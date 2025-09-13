#include "detectors/SessionEndDataReady.h"

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




Processor::Detector::SessionEndDataReady::SessionEndDataReady() :
    Processor::Detector::Interface() {



}



const Processor::Detector::Type Processor::Detector::SessionEndDataReady::GetType() const {

    return Processor::Detector::Type::SessionEndDataReady;

}



void Processor::Detector::SessionEndDataReady::Init(Processor::Data::SessionRecord* sessionRecord,
                std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords) {

    if (m_sessionRecord && m_driverRecords) return;

    Processor::Detector::Interface::doInit(sessionRecord, driverRecords);

    if (m_sessionRecord && m_driverRecords) {

        m_workerThread = std::thread(&Processor::Detector::SessionEndDataReady::Exec, this);

    }

}



void Processor::Detector::SessionEndDataReady::Exec() {

    while (m_sessionRecord && m_driverRecords) {


        std::map<const uint8_t, bool> participantTracker;
        //bool isAllFinished = m_sessionRecord->Finalized();




        // Thread is executed at 10Hz
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }

}