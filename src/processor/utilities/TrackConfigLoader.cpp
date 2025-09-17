#include "utilities/TrackConfigLoader.h"

#include <cstdint>
#include <cmath>
#include <filesystem>
#include <string>
#include <vector>
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

    std::vector<Lap::Internal::Sector> sectors;
    std::vector<Lap::Internal::Sector> minisectors;
    uint8_t latestSectorID = 1;
    uint8_t latestMiniSectorOrderID = 1;

    for (const auto& sectorNode : layout.children("sector")) {
        
        float_t start = UINT32_MAX;
        float_t end = 0;

        uint8_t latestMiniSectorUniqueID = 1;
        for (const auto& miniNode : sectorNode.children("minisector")) {
            
            float_t miniStart = miniNode.attribute("start").as_float();
            float_t miniEnd = miniNode.attribute("end").as_float();
            
            if (miniStart < start) start = miniStart;
            if (miniEnd > end) end = miniEnd;

            // The number of minisectors/lap can be assumed as zero as this is merely a template
            Lap::Internal::Sector s{ latestMiniSectorOrderID, latestMiniSectorUniqueID, 0, 0, miniStart, miniEnd};
            minisectors.push_back(s);
            ++latestMiniSectorOrderID;
            ++latestMiniSectorUniqueID;

        }
        // The number of sectors/lap can be assumed as zero as this is merely a template
        Lap::Internal::Sector s{ latestSectorID, 0, 0, start, end};
        sectors.push_back(s);
        ++latestSectorID;

    }

    trackData.setSectorInfo(sectors);
    return trackData;

}