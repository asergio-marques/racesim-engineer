#ifndef PROCESSOR_DETECTOR_INCLUDE_WARNING_PENALTY_H_
#define PROCESSOR_DETECTOR_INCLUDE_WARNING_PENALTY_H_

#include "detectors/Interface.h"
#include "detectors/Type.h"



namespace Processor {

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

            // Interface function to create new packets for communicating changes to the UI
            void AddWarnPenChange(const int8_t id, const int8_t diffWarns,
                const int8_t diffTrackLims, const int32_t diffTimePens,
                const int8_t diffStopGo, const int8_t diffDriveThrough);

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_WARNING_PENALTY_H_