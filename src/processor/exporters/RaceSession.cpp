#include "exporters/RaceSession.h"

#include <cstdint>
#include <map>
#include <string>
#include "exporters/Interface.h"
#include "FileIO.h"




Processor::Exporter::RaceSession::RaceSession() :
    Processor::Exporter::Interface(),
    m_driverRecords(nullptr),
    m_sessionRecord(nullptr) {

}



void Processor::Exporter::RaceSession::InjectRecords(
    std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords,
    Processor::Data::SessionRecord* sessionRecord) {

    if (driverRecords && sessionRecord) {

        m_driverRecords = driverRecords;
        m_sessionRecord = sessionRecord;

    }

}


#include <iostream>
void Processor::Exporter::RaceSession::Export(Processor::IFileIO* fileWriter, const std::string path) const {

    std::cout << "Path for export: " << path << std::endl;

}