#ifndef PROCESSOR_DATA_INCLUDE_LAP_TRACK_DATA_H_
#define PROCESSOR_DATA_INCLUDE_LAP_TRACK_DATA_H_

#include "data/internal/Session.h"




namespace Processor {

    namespace Detector {

        class LapFinished;
        class Interface;
        class TyreChanged;

    }

    namespace Data {

        class TrackData {

            public:
            // Constructor
            TrackData(const Session::Internal::TrackInfo baseInfo);

            // Destructor
            ~TrackData() = default;

        };

    }

}

#endif //  PROCESSOR_DATA_INCLUDE_LAP_TRACK_DATA_H_