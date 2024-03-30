#ifndef PROCESSOR_DETECTOR_INCLUDE_WARNING_PENALTY_H_
#define PROCESSOR_DETECTOR_INCLUDE_WARNING_PENALTY_H_

#include "detectors/Interface.h"
#include "detectors/Type.h"



namespace Processor {

    namespace Data {

        class DataInterface;

    }

    namespace Detector {

        class WarningPenalty final : public Processor::Detector::Interface {

            public:
            // Default constructor
            WarningPenalty() = default;

            // Default destructor
            ~WarningPenalty() = default;

            // Returns the identifying type of this detector
            const Processor::Detector::Type GetType() const override;

            // Main execution function
            void Exec() override final;

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_WARNING_PENALTY_H_