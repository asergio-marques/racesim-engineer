#include "detectors/WarningPenalty.h"

#include <chrono>
#include <thread>
#include "detectors/Interface.h"
#include "detectors/Type.h"



const Processor::Detector::Type Processor::Detector::WarningPenalty::GetType() const {

    return Processor::Detector::Type::WarningPenalty;

}



void Processor::Detector::WarningPenalty::Exec() {

    while (true) {

        // Thread is executed at 10Hz
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }

}