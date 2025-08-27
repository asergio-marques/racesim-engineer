#ifndef PROCESSOR_DETECTOR_INCLUDE_TYPE_H_
#define PROCESSOR_DETECTOR_INCLUDE_TYPE_H_

#include <cstdint>



namespace Processor {

    namespace Detector {

        enum class Type : uint8_t {

            Invalid                     = 0,
            SessionStartDataReady       = 1,
            ParticipantStatusChanged    = 2,
            Overtake                    = 3,
            LapFinished                 = 4,
            PenaltyReceived             = 5

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_TYPE_H_
