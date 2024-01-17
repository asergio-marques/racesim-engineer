#include "detectors/WarningPenalty.h"

#include <chrono>
#include <thread>
#include "detectors/Interface.h"



Processor::Detector::WarningPenalty::WarningPenalty(const Processor::Data::Databank* const dataBank) :
    Processor::Detector::Interface(dataBank) {



}



Processor::Detector::WarningPenalty::~WarningPenalty() {



}



void Processor::Detector::WarningPenalty::ReceiveNewData(Packet::Internal::Interface* const packet) {



}



void Processor::Detector::WarningPenalty::Exec() {

    while (true) {

        // Thread is executed at 10Hz
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

    }

}