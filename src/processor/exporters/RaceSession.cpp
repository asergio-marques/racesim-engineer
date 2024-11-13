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
    
    path = "C:/Users/dusk_/Documents/now.xml";
    std::cout << "Path for export: " << path << std::endl;

    pugi::xml_document doc;
    pugi::xml_node rootNode = doc.append_child("race");

    pugi::xml_node trackNode = rootNode.append_child("track");
    trackNode.append_child("id").append_child(pugi::node_pcdata).set_value("1");
    trackNode.append_child("name").append_child(pugi::node_pcdata).set_value("interlagos");

    rootNode.append_child("numLaps").append_child(pugi::node_pcdata).set_value("36");
    rootNode.append_child("completion").append_child(pugi::node_pcdata).set_value("true");

    std::cout << "Saving result: " << doc.save_file(path.c_str()) << std::endl;

}