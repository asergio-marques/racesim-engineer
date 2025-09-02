#ifndef PROCESSOR_DETECTOR_INCLUDE_TYRE_CHANGED_H_
#define PROCESSOR_DETECTOR_INCLUDE_TYRE_CHANGED_H_

#include <cstdint>
#include <map>
#include "data/internal/TyreData.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"




namespace Processor {

    namespace Data {

        class DriverRecord;
        class SessionRecord;

    }

    namespace Detector {

        class TyreChanged final : public Processor::Detector::Interface {

            public:
            // Default constructor
            TyreChanged() = default;

            // Default destructor
            ~TyreChanged() = default;

            // Returns the identifying type of this detector
            const Processor::Detector::Type GetType() const override;

            // Initializes the session record, forgoing the worker thread as it is not necessary
            virtual void Init(Processor::Data::SessionRecord* sessionRecord,
                std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords) override final;

            // Prepares a packet informing that a change of tyres was performed
            void addTyreChangeInfo(const uint8_t driverID, const Tyre::Internal::Data newTyreData);

            private:
            // Main execution function (does nothing)
            void Exec() override final {};

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_TYRE_CHANGED_H_