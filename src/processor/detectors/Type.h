#ifndef PROCESSOR_DETECTOR_INCLUDE_TYPE_H_
#define PROCESSOR_DETECTOR_INCLUDE_TYPE_H_

#include <cstdint>



namespace Processor {

    namespace Detector {

        enum class Type : uint8_t {

            Invalid                     = 0,
            SessionStartDataReady       = 1,
            SessionEndDataReady         = 2,
            ParticipantStatusChanged    = 3,
            Overtake                    = 4,
            LapFinished                 = 5,
            PenaltyReceived             = 6,
            TyreChanged                 = 7,
            SectorStateChanged          = 8,
            SectorFinished              = 9

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_TYPE_H_
