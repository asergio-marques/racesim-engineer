#include "detectors/SessionStartDataReady.h"

#include "detectors/Interface.h"
#include "detectors/Type.h"



Processor::Detector::SessionStartDataReady::SessionStartDataReady() :
    Processor::Detector::Interface::Interface(),
    m_sentSessionStart(false) {



}


const Processor::Detector::Type Processor::Detector::SessionStartDataReady::GetType() const {

    return Processor::Detector::Type::SessionStartDataReady;

}



bool Processor::Detector::SessionStartDataReady::RegisterFunction(std::function<void(bool)> f) {

    // Validate function pointer received
    if (f) {

        // Always overwrite the already-existing pointer
        m_regFunc = f;
        return true;

    }

    return false;

}



void Processor::Detector::SessionStartDataReady::DeregisterFunction() {

    m_regFunc = nullptr;

}



void Processor::Detector::SessionStartDataReady::Exec() {

    while (!m_sentSessionStart) {

        // TODO check for all the data having been "readied", then prepare the adequate event packet
        // after having prepared the event packet, do the callback for special operations
        if (false) {
            m_regFunc(true);
        }
        // Thread is executed at 10Hz
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }

}