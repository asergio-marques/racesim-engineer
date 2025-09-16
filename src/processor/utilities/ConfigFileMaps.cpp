#include "utilities/ConfigFileMaps.h"

#include <map>
#include <string>
#include "data/internal/Session.h"




const std::vector<Session::Internal::Track>
Processor::Utility::ConfigFileMaps::SUPPORTED_TRACKS = {

    Session::Internal::Track::AUS_Melbourne

};



const std::map<Session::Internal::Track, std::string>
Processor::Utility::ConfigFileMaps::ID_FILENAME_MAP = {

    { Session::Internal::Track::AUS_Melbourne, "1_AlbertPark" }

};