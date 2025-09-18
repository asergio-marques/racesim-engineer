#include "detectors/SectorStateChanged.h"

#include "detectors/Interface.h"
#include "detectors/Type.h"




const Processor::Detector::Type Processor::Detector::SectorStateChanged::GetType() const {

    return Processor::Detector::Type::SectorStateChanged;

}



void Processor::Detector::SectorStateChanged::Init(Processor::Data::SessionRecord* sessionRecord,
    std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords) {

    if (m_sessionRecord && m_driverRecords) return;

    Processor::Detector::Interface::doInit(sessionRecord, driverRecords);

}



void Processor::Detector::SectorStateChanged::Deinit() {

    if (!m_sessionRecord || !m_driverRecords) return;

    Processor::Detector::Interface::doDeinit();

}



void Processor::Detector::SectorStateChanged::AddSectorChangeInfo() {

    // TODO

}