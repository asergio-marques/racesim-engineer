#include "exporters/RaceSession.h"

#include <cstdint>
#include <map>
#include <string>
#include <pugixml.hpp>
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
void Processor::Exporter::RaceSession::Export(Processor::IFileIO* fileWriter, std::string path) const {
    
    path += "/now.xml";
    std::cout << "Path for export: " << path << std::endl;

    pugi::xml_document doc;
    auto node = doc.append_child("laps");
    auto node1 = node.append_child("1");
    std::cout << "Saving result: " << doc.save_file(path.c_str()) << std::endl;

}