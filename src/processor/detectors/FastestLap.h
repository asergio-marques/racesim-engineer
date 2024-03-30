#ifndef PROCESSOR_DETECTOR_INCLUDE_FASTEST_LAP_H_
#define PROCESSOR_DETECTOR_INCLUDE_FASTEST_LAP_H_

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

            // Main execution function
            void Exec() override final;

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_FASTEST_LAP_H_