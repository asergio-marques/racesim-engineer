#include "data/Databank.h"

#include "data/DriverRecord.h"
#include "data/SessionRecord.h"



Processor::Data::Databank::Databank() :
    m_driverRecords(),
    m_sessionRecord(nullptr) {



}



Processor::Data::Databank::~Databank() {

    for (auto record : m_driverRecords) {

        delete record;

    }
    m_driverRecords.clear();
    delete m_sessionRecord;

}