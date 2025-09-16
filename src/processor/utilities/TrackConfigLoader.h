#ifndef PROCESSOR_UTILITIES_TRACK_CONFIG_LOADER_H_
#define PROCESSOR_UTILITIES_TRACK_CONFIG_LOADER_H_

#include <string>
#include "data/holders/TrackData.h"
#include "data/internal/Session.h"




namespace Processor {

    namespace Utility {

        class TrackConfigLoader  {

            public:
            TrackConfigLoader(Session::Internal::Track id);
            virtual ~TrackConfigLoader() = default;

            // Performs the actual reading of the track config file
            Processor::Data::TrackData readConfig() const;

            private:
            // Non-mutable identifier of the track which this object is set to read the config of
            const Session::Internal::Track m_ID;

            // Path to the directory in which the track config files are kept
            static const std::string TRACK_CONFIG_DIR;

        }

    }

}


#endif // PROCESSOR_UTILITIES_TRACK_CONFIG_LOADER_H_