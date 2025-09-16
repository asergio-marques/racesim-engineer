#ifndef PROCESSOR_UTILITIES_CONFIG_FILE_MAPS_H_
#define PROCESSOR_UTILITIES_CONFIG_FILE_MAPS_H_

#include <map>
#include <string>
#include <vector>
#include "data/internal/Session.h"


namespace Processor {

    namespace Utility {

        struct ConfigFileMaps {

            // Lists all tracks with detailed data support
            static const std::vector<Session::Internal::Track> SUPPORTED_TRACKS;

            // Maps the track IDs to the config file's names
            static const std::map<Session::Internal::Track, std::string> ID_FILENAME_MAP;
    
        };

    }

}

#endif // PROCESSOR_UTILITIES_CONFIG_FILE_MAPS_H_