#ifndef PROCESSOR_DETECTOR_INCLUDE_SESSION_END_DATA_READY_H_
#define PROCESSOR_DETECTOR_INCLUDE_SESSION_END_DATA_READY_H_

#include <cstdint>
#include <map>
#include <vector>
#include "data/internal/Participant.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"



namespace Processor {

    namespace Data {

        class DriverRecord;
        class SessionRecord;

    }

    namespace Detector {

        class SessionEndDataReady final : public Processor::Detector::Interface {

            public:
            // Default constructor
            SessionEndDataReady();

            // Default destructor
            ~SessionEndDataReady() = default;

            // Returns the identifying type of this detector
            const Processor::Detector::Type GetType() const override final;

            // Initializes the session record, and utilizes the worker thread
            void Init(Processor::Data::SessionRecord* sessionRecord,
                std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords) override final;

            private:
            // Main execution function to be overridden by all concrete detectors
            void Exec() override final;

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_SESSION_END_DATA_READY_H_