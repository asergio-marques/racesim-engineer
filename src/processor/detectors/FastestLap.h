#ifndef PROCESSOR_DETECTOR_INCLUDE_FASTEST_LAP_H_
#define PROCESSOR_DETECTOR_INCLUDE_FASTEST_LAP_H_

#include "data/holders/LapInfo.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"



namespace Processor {

    namespace Detector {

        class FastestLap final : public Processor::Detector::Interface {

            public:
            // Default constructor
            FastestLap() = default;

            // Default destructor
            ~FastestLap() = default;

            // Returns the identifying type of this detector
            const Processor::Detector::Type GetType() const override;

            // Compares a new completed lap with the current session best,
            // returning true and preparing the packet if this lap is indeed the session best
            bool checkFastestInSession(const Processor::Data::LapInfo& finishedLap);

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_FASTEST_LAP_H_