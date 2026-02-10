#ifndef PROCESSOR_DETECTOR_INCLUDE_INFO_SYNCHRONIZER_H_
#define PROCESSOR_DETECTOR_INCLUDE_INFO_SYNCHRONIZER_H_

#include <cstdint>
#include <vector>
#include "detectors/Interface.h"
#include "detectors/Type.h"



namespace Processor {

    namespace Data {

        class DriverRecord;
        class SessionRecord;

    }

    namespace Detector {

        class InfoSynchronizer final : public Processor::Detector::Interface {

            public:
            // Default constructor
            InfoSynchronizer() = default;

            // Default destructor
            ~InfoSynchronizer() = default;

            // Initializes the session record, and utilizes the worker thread
            void Init(Processor::Data::SessionRecord* sessionRecord,
                std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords) override final;

            // Clears all data to ready the detector for a new session
            void Deinit() override final;

            // Returns the identifying type of this detector
            const Processor::Detector::Type GetType() const override;

            private:
            // Main execution function
            void Exec() override final;

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_INFO_SYNCHRONIZER_H_