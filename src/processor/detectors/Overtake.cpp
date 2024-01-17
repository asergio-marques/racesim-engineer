#include "detectors/Overtake.h"

#include <chrono>
#include <thread>
#include "detectors/Interface.h"



Processor::Detector::Overtake::Overtake(const Processor::Data::Databank* const dataBank) :
    Processor::Detector::Interface(dataBank) {



}



Processor::Detector::Overtake::~Overtake() {



}



void Processor::Detector::Overtake::ReceiveNewData(Packet::Internal::Interface* const packet) {



}



void Processor::Detector::Overtake::Exec() {

    while (true) {

        // Thread is executed at 10Hz
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

    }

}