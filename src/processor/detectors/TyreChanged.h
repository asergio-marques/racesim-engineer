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

            // Special function to inject the driver records into this detector, rather than the other way around
            bool InstallDriverRecords(std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords);

            // Prepares a packet informing that a change of tyres was performed
            void addTyreChangeInfo(const uint8_t driverID, const Tyre::Internal::Data newTyreData);
            
            private:
            // Pointer to the currently active driver records
            std::map<const uint8_t, Processor::Data::DriverRecord*>* m_driverRecords = nullptr;

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_TYRE_CHANGED_H_