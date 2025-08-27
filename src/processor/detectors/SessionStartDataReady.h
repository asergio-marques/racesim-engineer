#ifndef PROCESSOR_DETECTOR_INCLUDE_SESSION_START_DATA_READY_H_
#define PROCESSOR_DETECTOR_INCLUDE_SESSION_START_DATA_READY_H_

#include <cstdint>
#include <vector>
#include "data/internal/Participant.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"



namespace Processor {

    namespace Detector {

        class SessionStartDataReady final : public Processor::Detector::Interface {

            public:
            // Default constructor
            SessionStartDataReady() = default;

            // Default destructor
            ~SessionStartDataReady() = default;

            // Returns the identifying type of this detector
            const Processor::Detector::Type GetType() const override;

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_SESSION_START_DATA_READY_H_