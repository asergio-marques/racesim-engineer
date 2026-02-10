#ifndef PROCESSOR_DETECTOR_INCLUDE_TYPE_H_
#define PROCESSOR_DETECTOR_INCLUDE_TYPE_H_

#include <cstdint>



namespace Processor {

    namespace Detector {

        enum class Type : uint8_t {

            Invalid                     = 0,
            SessionStartDataReady       = 1,
            SessionEndDataReady         = 2,
            InfoSynchronizer            = 3,
            ParticipantStatusChanged    = 4,
            Overtake                    = 5,
            LapFinished                 = 6,
            PenaltyReceived             = 7,
            TyreChanged                 = 8,
            SectorStateChanged          = 9

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_TYPE_H_
