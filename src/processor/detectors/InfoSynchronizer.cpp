#include "detectors/InfoSynchronizer.h"

#include <chrono>
#include <cstdint>
#include <thread>
#include <vector>
#include <QSharedPointer>
#include "detectors/Interface.h"
#include "detectors/Type.h"



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

        // Data sync is only meant to happen once every 10 seconds, to minimize load
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

    }

}