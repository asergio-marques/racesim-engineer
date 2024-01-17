#include "detectors/Interface.h"

#include <thread>
#include <vector>



Processor::Detector::Interface::Interface(const Processor::Data::Databank* const dataBank) :
    m_data(dataBank),
    m_workerThread() {



}



Processor::Detector::Interface::~Interface() {



}



void Processor::Detector::Interface::Init() {

    m_workerThread = std::thread(&Processor::Detector::Interface::Exec, this);

}