#include "utilities/TrackConfigLoader.h"

#include <string>
#include "data/internal/Session.h"
#include "utilities/ConfigFileMaps.h"




const std::string Processor::Utility::TrackConfigLoader::TRACK_CONFIG_DIR = "./config/tracks/";



Processor::Utility::TrackConfigLoader::TrackConfigLoader(Session::Internal::Track id) :
    m_ID(id) {



}



Processor::Data::TrackData Processor::Utility::TrackConfigLoader::readConfig() const {

    ok = false;

}