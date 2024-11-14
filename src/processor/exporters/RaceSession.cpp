#include "exporters/RaceSession.h"

#include <cstdint>
#include <map>
#include <string>
#include <pugixml.hpp>
#include "exporters/Interface.h"
#include "data/SessionRecord.h"
#include "data/SessionState.h"




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
    addChildNodeCharacterData(&rootNode, m_schemaV1.versionTag,
        m_schemaV1.version);
    addChildNodeCharacterData(&rootNode, m_schemaV1.trackIdTag,
        static_cast<uint8_t>(m_sessionRecord->getTrackID()));
    // addChildNodeCharacterData(&rootNode, m_schemaV1.trackNameTag, ConvertTrackId(m_sessionRecord->getTrackID()));
    addChildNodeCharacterData(&rootNode, m_schemaV1.numLapsTag,
        static_cast<uint8_t>(m_sessionRecord->getTotalLaps()));
    // TODO what's the best nonintrusive way of peeking into a state that isn't gets out the ass?

    /*rootNode.append_child(m_schemaV1.fastestOverallTag).append_child(pugi::node_pcdata).set_value("1:08.048");
    rootNode.append_child(m_schemaV1.completionTag).append_child(pugi::node_pcdata).set_value("true");
    rootNode.append_child(m_schemaV1.gridPosTag).append_child(pugi::node_pcdata).set_value("2");
    pugi::xml_node lapsNode = rootNode.append_child("laps");
    for (size_t i = 1; i <= 36; ++i) {
        pugi::xml_node lapNode = lapsNode.append_child("lap");
        lapNode.append_child("id").append_child(pugi::node_pcdata).set_value(std::to_string(i).c_str());
        lapNode.append_child("totalLapTime").append_child(pugi::node_pcdata).set_value("1:08.048");
        lapNode.append_child("sector1Time").append_child(pugi::node_pcdata).set_value("18.158");
        lapNode.append_child("sector2Time").append_child(pugi::node_pcdata).set_value("33.925");
        lapNode.append_child("sector3Time").append_child(pugi::node_pcdata).set_value("15.965");
        lapNode.append_child("tyreType").append_child(pugi::node_pcdata).set_value("S");
        lapNode.append_child("tyreCompound").append_child(pugi::node_pcdata).set_value("C4");
        lapNode.append_child("energyDelta").append_child(pugi::node_pcdata).set_value("10.032");
        lapNode.append_child("energyRechargePercent").append_child(pugi::node_pcdata).set_value("0.82");
        lapNode.append_child("fuelDeltaKg").append_child(pugi::node_pcdata).set_value("-0.68");
        lapNode.append_child("numDRSAct").append_child(pugi::node_pcdata).set_value("2");
        lapNode.append_child("trackConditions").append_child(pugi::node_pcdata).set_value("Dry");
        lapNode.append_child("deltaLeaderAtEnd").append_child(pugi::node_pcdata).set_value("0.000");
        lapNode.append_child("deltaFrontAtEnd").append_child(pugi::node_pcdata).set_value("0.000");
        lapNode.append_child("deltaBackAtEnd").append_child(pugi::node_pcdata).set_value("-2.315");
        lapNode.append_child("positionAtEnd").append_child(pugi::node_pcdata).set_value("1");
        lapNode.append_child("trackLimits").append_child(pugi::node_pcdata).set_value("1");
        lapNode.append_child("otherWarns").append_child(pugi::node_pcdata).set_value("0");
        lapNode.append_child("timePens").append_child(pugi::node_pcdata).set_value("0");
        lapNode.append_child("driveThroughs").append_child(pugi::node_pcdata).set_value("0");
        lapNode.append_child("other").append_child(pugi::node_pcdata).set_value("");
    }*/

    std::cout << "Saving result: " << doc.save_file(path.c_str()) << std::endl;

}


void Processor::Exporter::RaceSession::addChildNodeCharacterData(pugi::xml_node* parentNode, const char* tag, const char* value)  const {

    parentNode->append_child(tag).append_child(pugi::node_pcdata).set_value(value);

}


void Processor::Exporter::RaceSession::addChildNodeCharacterData(pugi::xml_node* parentNode, const char* tag, const std::string& value) const {

    addChildNodeCharacterData(parentNode, tag, value.c_str());

}



void Processor::Exporter::RaceSession::addChildNodeCharacterData(pugi::xml_node* parentNode, const char* tag, uint8_t value) const {

    addChildNodeCharacterData(parentNode, tag, std::to_string(value).c_str());

}



void Processor::Exporter::RaceSession::addChildNodeCharacterData(pugi::xml_node* parentNode, const char* tag, uint16_t value) const {

    addChildNodeCharacterData(parentNode, tag, std::to_string(value).c_str());

}



void Processor::Exporter::RaceSession::addChildNodeCharacterData(pugi::xml_node* parentNode, const char* tag, uint32_t value) const {

    addChildNodeCharacterData(parentNode, tag, std::to_string(value).c_str());

}