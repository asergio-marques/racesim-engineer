#include "exporters/RaceSession.h"

#include <chrono>
#include <cstdint>
#include <map>
#include <string>
#include <pugixml.hpp>
#include "exporters/Interface.h"
#include "data/DriverRecord.h"
#include "data/DriverState.h"
#include "data/SessionRecord.h"
#include "data/SessionState.h"




Processor::Exporter::RaceSession::RaceSession() :
    Processor::Exporter::Interface(),
    m_playerDriverRecord(nullptr),
    m_sessionRecord(nullptr),
    m_driverRecords(nullptr) {

}



void Processor::Exporter::RaceSession::InjectRecords(Processor::Data::SessionRecord* sessionRecord, Processor::Data::DriverRecord* driverRecord) {

    // double check if what we are trying to insert is the same as before, no point if it is
    if (driverRecord && (driverRecord != m_playerDriverRecord)) {

        m_playerDriverRecord = driverRecord;

    }
    if (sessionRecord && (sessionRecord != sessionRecord)) {

        m_sessionRecord = sessionRecord;

    }

}


void Processor::Exporter::RaceSession::InjectRecords(Processor::Data::SessionRecord* sessionRecord,
    std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords) {

    if (driverRecords && sessionRecord) {

        m_sessionRecord = sessionRecord;
        m_driverRecords = driverRecords;

    }

}



bool Processor::Exporter::RaceSession::Export(std::string path) const {

    // actual code
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    const auto nowtm = localtime(&now);
    std::string filename = "Race_" +
        std::to_string(nowtm->tm_year + 1900) + "_" +
        std::to_string(nowtm->tm_mon) + "_" +
        std::to_string(nowtm->tm_mday) + "_" +
        std::to_string(nowtm->tm_hour) + "_" +
        std::to_string(nowtm->tm_min) + "_" +
        std::to_string(nowtm->tm_sec) + ".xml";
    if (path.at(path.size() - 1) == '\\') {
        path += filename;
    }
    else {
        path += "\\" + filename;
    }
    pugi::xml_document doc;
    pugi::xml_node rootNode = doc.append_child("race");

    if (m_sessionRecord) {

        addChildNodeCharacterData(&rootNode, m_schemaV1.versionTag,
            m_schemaV1.version);
        addChildNodeCharacterData(&rootNode, m_schemaV1.trackIdTag,
            static_cast<uint8_t>(m_sessionRecord->getTrackInfo().m_sessionTrack));
        // TODO: converter map
        // addChildNodeCharacterData(&rootNode, m_schemaV1.trackNameTag, ConvertTrackId(m_sessionRecord->getTrackID()));
        addChildNodeCharacterData(&rootNode, m_schemaV1.numLapsTag,
            static_cast<uint8_t>(m_sessionRecord->getSessionSettings().m_sessionDurationLaps));
        addChildNodeCharacterData(&rootNode, m_schemaV1.fastestOverallTag,
            m_sessionRecord->getModifiableState().fastestLap().m_totalLapTime);

    }
    if (m_playerDriverRecord) {
        addChildNodeCharacterData(&rootNode, m_schemaV1.completionTag,
            m_playerDriverRecord->isFinished());
        addChildNodeCharacterData(&rootNode, m_schemaV1.gridPosTag,
            m_playerDriverRecord->getModifiableState().posTimeData().getGridPosition());

        pugi::xml_node lapsNode = rootNode.append_child("laps");
        const auto& lapData = m_playerDriverRecord->getModifiableState().lapData();
        for (size_t i = 1; i <= lapData.numLapsAvailable(); ++i) {

            const auto* lap = lapData.getLapData(i);
            if (lap) {

                pugi::xml_node lapNode = lapsNode.append_child("lap");
                addChildNodeCharacterData(&lapNode, m_schemaV1.lapIdTag, lap->m_lapId);
                addChildNodeCharacterData(&lapNode, m_schemaV1.lapTimeTag, lap->m_totalLapTime);
                addChildNodeCharacterData(&lapNode, m_schemaV1.sector1TimeTag, lap->m_sector1Time);
                addChildNodeCharacterData(&lapNode, m_schemaV1.sector2TimeTag, lap->m_sector2Time);
                addChildNodeCharacterData(&lapNode, m_schemaV1.sector3TimeTag, lap->m_sector3Time);

                // TODO: these values are only prepared code, but it's unused right now
                // addChildNodeCharacterData(&lapNode, m_schemaV1.tyreVisualTag, readableTyreData(lap->m_visualTyre));
                // addChildNodeCharacterData(&lapNode, m_schemaV1.tyreCompoundTag, readableTyreData(lap->m_actualTyre));
                // addChildNodeCharacterData(&lapNode, m_schemaV1.energyDeltaTag, lap->m_ersEnergyAtEnd - lap->m_ersEnergyAtStart);
                // addChildNodeCharacterData(&lapNode, m_schemaV1.energyRechargeTag, lap->m_ersEnergyRecharged);
                // addChildNodeCharacterData(&lapNode, m_schemaV1.energyAllowanceTag, lap->m_ersLapAllowanceUnused);
                // addChildNodeCharacterData(&lapNode, m_schemaV1.fuelDeltaTag, lap->m_fuelLoadAtEnd - lap->m_fuelLoadAtStart);
                // addChildNodeCharacterData(&lapNode, m_schemaV1.drsActTag, lap->m_numDRSActivation);
                // addChildNodeCharacterData(&lapNode, m_schemaV1.trackCondTag, readableWeatherConditions(lap->m_conditions));
                // timeDeltaLeaderTag
                // timeDeltaFrontTag
                // timeDeltaBehindTag
                // lapPosTag
                // numTrackLimTag
                // numOtherWarnTag
                // numLapTimePensTag
                // numTotalTimePensTag
                // numLapDTTag
                // numTotalDTTag
                // otherTag

            }

        }
    }
    else if (m_driverRecords) {
        // don't do shit because I don't wanna have this headache rn
    }

    return doc.save_file(path.c_str());

}



void Processor::Exporter::RaceSession::addChildNodeCharacterData(pugi::xml_node* parentNode, const char* tag, const char* value)  const {

    parentNode->append_child(tag).append_child(pugi::node_pcdata).set_value(value);

}


void Processor::Exporter::RaceSession::addChildNodeCharacterData(pugi::xml_node* parentNode, const char* tag, const std::string& value) const {

    addChildNodeCharacterData(parentNode, tag, value.c_str());

}



void Processor::Exporter::RaceSession::addChildNodeCharacterData(pugi::xml_node* parentNode, const char* tag, bool value) const {

    if (value) addChildNodeCharacterData(parentNode, tag, "true");
    else addChildNodeCharacterData(parentNode, tag, "false");

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



void Processor::Exporter::RaceSession::addChildNodeCharacterData(pugi::xml_node* parentNode, const char* tag, const Lap::Internal::Time& value) const {

    // TODO later logic when import & comparison is working, for now use a simpler approach
    /*pugi::xml_node lapNode = parentNode->append_child(tag);
    lapNode.append_child(m_schemaV1.lapTimeSecTag).append_child(pugi::node_pcdata).set_value(std::to_string(value.m_seconds).c_str());
    lapNode.append_child(m_schemaV1.lapTimeMSecTag).append_child(pugi::node_pcdata).set_value(std::to_string(value.m_milliseconds).c_str());*/
    addChildNodeCharacterData(parentNode, tag, value.formattedPrint().c_str());

}