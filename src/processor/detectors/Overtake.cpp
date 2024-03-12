#include "detectors/Overtake.h"

#include <chrono>
#include <thread>
#include "data/Databank.h"
#include "data/DriverRecord.h"
#include "detectors/Interface.h"



Processor::Detector::Overtake::Overtake(const Processor::Data::DataInterface* const dataBank) :
    Processor::Detector::Interface(dataBank) {



}



Processor::Detector::Overtake::~Overtake() {



}



const Processor::Detector::Type Processor::Detector::Overtake::GetType() const {

    return Processor::Detector::Type::Overtake;

}



void Processor::Detector::Overtake::Exec() {

    while (true) {

        if (m_data) {

            const auto newRecords = m_data->getDriverRecords();

            for (size_t i = 0; i < m_referenceRecord.size(); ++i) {
                
                const auto record = newRecords.find(i)->second;
                const auto refRecord = m_referenceRecord.find(i)->second;

                if (record && refRecord &&
                    (record->getLastTimestamp() > refRecord->getLastTimestamp()))
                {
                    //record->getModifiableState().getCurrentPosition() != refRecord->getModifiableState().getCurrentPosition();
                }

            }

            m_referenceRecord = newRecords;

        }

        // Thread is executed at 100Hz
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

    }

}