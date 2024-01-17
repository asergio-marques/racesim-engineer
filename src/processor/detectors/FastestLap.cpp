#include "detectors/FastestLap.h"

#include <chrono>
#include <thread>
#include "detectors/Interface.h"



Processor::Detector::FastestLap::FastestLap(const Processor::Data::Databank* const dataBank) :
    Processor::Detector::Interface(dataBank) {



}



Processor::Detector::FastestLap::~FastestLap() {



}



void Processor::Detector::FastestLap::ReceiveNewData(Packet::Internal::Interface* const packet) {

    

}



void Processor::Detector::FastestLap::Exec() {

    while (true) {

        // Thread is executed at 10Hz
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

    }

}