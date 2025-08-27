#ifndef PROCESSOR_DETECTOR_INCLUDE_LAP_FINISHED_H_
#define PROCESSOR_DETECTOR_INCLUDE_LAP_FINISHED_H_

#include "data/holders/LapInfo.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"



namespace Processor {

    namespace Detector {

        class LapFinished final : public Processor::Detector::Interface {

            public:
            // Default constructor
            LapFinished() = default;

            // Default destructor
            ~LapFinished() = default;

            // Returns the identifying type of this detector
            const Processor::Detector::Type GetType() const override;

            // Compares a new completed lap with the current session best,
            // returning true and preparing the packet if this lap is indeed the session best
            bool checkFastestInSession(const Processor::Data::LapInfo& finishedLap);

            // Prepares a packet for a newly-finished lap
            void addFinishedLapInfo(const Processor::Data::LapInfo& finishedLap, const Lap::Internal::InfoType infoType);

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_LAP_FINISHED_H_