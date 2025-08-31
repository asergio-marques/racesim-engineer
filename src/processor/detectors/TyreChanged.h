#ifndef PROCESSOR_DETECTOR_INCLUDE_TYRE_CHANGED_H_
#define PROCESSOR_DETECTOR_INCLUDE_TYRE_CHANGED_H_

#include "data/internal/TyreData.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"




namespace Processor {

    namespace Detector {

        class TyreChanged final : public Processor::Detector::Interface {

            public:
            // Default constructor
            TyreChanged() = default;

            // Default destructor
            ~TyreChanged() = default;

            // Returns the identifying type of this detector
            const Processor::Detector::Type GetType() const override;

            // Prepares a packet informing that a change of tyres was performed
            void addTyreChangeInfo(const uint8_t driverID, const Tyre::Internal::Data newTyreData);

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_TYRE_CHANGED_H_