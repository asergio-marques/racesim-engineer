#ifndef PROCESSOR_DETECTOR_INCLUDE_TYPE_H_
#define PROCESSOR_DETECTOR_INCLUDE_TYPE_H_

#include <cstdint>



namespace Processor {

    namespace Detector {

        enum class Type : uint8_t {

            Invalid             = 0,
            Overtake            = 1,
            FastestLap          = 2,
            WarningPenalty      = 3,
            ParticipantStatus   = 4

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_TYPE_H_
