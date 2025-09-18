#include "detectors/SectorFinished.h"

#include "detectors/Interface.h"
#include "detectors/Type.h"




const Processor::Detector::Type Processor::Detector::SectorFinished::GetType() const {

    return Processor::Detector::Type::SectorFinished;

}



void Processor::Detector::SectorFinished::Init(Processor::Data::SessionRecord* sessionRecord,
    std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords) {

    if (m_sessionRecord && m_driverRecords) return;

    Processor::Detector::Interface::doInit(sessionRecord, driverRecords);

}



void Processor::Detector::SectorFinished::Deinit() {

    if (!m_sessionRecord || !m_driverRecords) return;

    Processor::Detector::Interface::doDeinit();

}



void Processor::Detector::SectorFinished::AddFinishedSectorInfo() {

    // TODO

}