#include "detectors/SessionStartDataReady.h"

#include "detectors/Interface.h"
#include "detectors/Type.h"



Processor::Detector::SessionStartDataReady::SessionStartDataReady() :
    Processor::Detector::Interface(),
    m_sentSessionStart(false) {



}


const Processor::Detector::Type Processor::Detector::SessionStartDataReady::GetType() const {

    return Processor::Detector::Type::SessionStartDataReady;

}



void Processor::Detector::SessionStartDataReady::Exec() {

    while (!m_sentSessionStart) {

        if (m_installedInDriverRecords && m_sessionRecord) {

            // TODO prepare event packet

        }
        // Thread is executed at 10Hz
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }

}