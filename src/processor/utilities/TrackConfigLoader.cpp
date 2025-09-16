#include "utilities/TrackConfigLoader.h"

#include <filesystem>
#include <map>
#include <string>
#include <pugixml.hpp>
#include "data/internal/Session.h"
#include "data/holders/TrackData.h"
#include "utilities/ConfigFileMaps.h"




const std::string Processor::Utility::TrackConfigLoader::CONFIG_DIR = "config";
const std::string Processor::Utility::TrackConfigLoader::TRACKS_DIR = "tracks";



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
    std::filesystem::path trackConfigDir = std::filesystem::current_path() /
        Processor::Utility::TrackConfigLoader::CONFIG_DIR /
        Processor::Utility::TrackConfigLoader::TRACKS_DIR;
    std::filesystem::path fullPath = trackConfigDir / (filenameIt->second + ".xml");

    if (!std::filesystem::exists(fullPath)) {

        return trackData;

    }

    pugi::xml_document doc;
    if (!doc.load_file(fullPath.string().c_str())) {

        return trackData;

    }

    pugi::xml_node root = doc.child("track");
    // check ID validity
    if (!root || root.attribute("id").as_uint() != static_cast<uint8_t>(m_ID)) {
        return trackData;
    }

    // hardcoded to layout id 0 for the time being
    pugi::xml_node layout = root.find_child_by_attribute("layout", "id", "0");
    if (!layout) {

        return trackData;

    }

    std::map<uint8_t, Lap::Internal::Sector> sectors;
    uint8_t latestSectorID = 1;
    for (const auto& sectorNode : layout.children("sector")) {
        
        uint32_t start = UINT32_MAX;
        uint32_t end = 0;

        std::map<uint8_t, Lap::Internal::Sector> miniSectors;
        uint8_t latestMiniSectorID = 1;

        for (const auto& miniNode : sectorNode.children("minisector")) {
            
            uint32_t miniStart = miniNode.attribute("start").as_uint();
            uint32_t miniEnd = miniNode.attribute("end").as_uint();
            
            if (miniStart < start) start = miniStart;
            if (miniEnd > end) end = miniEnd;

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