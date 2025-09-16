#include "utilities/TrackConfigLoader.h"

#include <filesystem>
#include <map>
#include <string>
#include <pugixml.hpp>
#include "data/internal/Session.h"
#include "data/holders/TrackData.h"
#include "utilities/ConfigFileMaps.h"




const std::string Processor::Utility::TrackConfigLoader::TRACK_CONFIG_DIR = "./config/tracks";



Processor::Utility::TrackConfigLoader::TrackConfigLoader(Session::Internal::Track id) :
    m_ID(id) {



}



Processor::Data::TrackData Processor::Utility::TrackConfigLoader::readConfig() {
    
    Processor::Data::TrackData trackData{ m_ID, 0 };

    // get the filename based on the ID
    auto filenameIt = Processor::Utility::ConfigFileMaps::ID_FILENAME_MAP.find(m_ID);
    if (filenameIt == Processor::Utility::ConfigFileMaps::ID_FILENAME_MAP.end()) {

        return trackData;

    }
    std::filesystem::path trackConfigDir = Processor::Utility::TrackConfigLoader::TRACK_CONFIG_DIR;
    std::filesystem::path fullPath = trackConfigDir / (filenameIt->second + ".xml");

    if (!std::filesystem::is_regular_file(fullPath)) {

        return trackData;

    }

    pugi::xml_document doc;
    if (!doc.load_file(fullPath.string().c_str())) {

        return trackData;

    }

    // hardcoded to layout id 0 for the time being
    pugi::xml_node layout = doc.find_child_by_attribute("layout", "id", "0");
    if (!layout) {

        return trackData;

    }

    std::map<uint8_t, Lap::Internal::Sector> sectors;
    uint8_t latestSectorID = 1;
    for (pugi::xml_node sectorNode : layout.child("sectors").children("sector")) {
        
        uint32_t start = sectorNode.attribute("start").as_uint();
        uint32_t end = sectorNode.attribute("end").as_uint();

        std::map<uint8_t, Lap::Internal::Sector> miniSectors;
        uint8_t latestMiniSectorID = 1;

        for (pugi::xml_node miniNode : sectorNode.child("minisectors").children("minisector")) {
            
            uint32_t miniStart = miniNode.attribute("start").as_uint();
            uint32_t miniEnd = miniNode.attribute("end").as_uint();

            Lap::Internal::Sector s{ latestMiniSectorID, miniStart, miniEnd };
            miniSectors.emplace(latestMiniSectorID, s);
            ++latestMiniSectorID;

        }

        Lap::Internal::Sector s{ latestSectorID, start, end, miniSectors };
        sectors.emplace(latestSectorID, s);
        ++latestSectorID;

    }

    trackData.setSectorInfo(sectors);
    return trackData;

}