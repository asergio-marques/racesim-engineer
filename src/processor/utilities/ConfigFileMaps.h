#ifndef PROCESSOR_UTILITIES_CONFIG_FILE_MAPS_H_
#define PROCESSOR_UTILITIES_CONFIG_FILE_MAPS_H_

#include <map>
#include <string>
#include "data/internal/Session.h"


namespace Processor {

    namespace Utility {

        struct ConfigFileMaps {

            // Maps the track IDs to the config file's names
            static const std::map<Session::Internal::Track, std::string> ID_FILENAME_MAP;
    
        };

    }

}

#endif // PROCESSOR_UTILITIES_CONFIG_FILE_MAPS_H_