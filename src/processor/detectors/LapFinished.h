#ifndef PROCESSOR_DETECTOR_INCLUDE_LAP_FINISHED_H_
#define PROCESSOR_DETECTOR_INCLUDE_LAP_FINISHED_H_

#include "data/holders/LapInfo.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"



namespace Processor {

    namespace Data {

        class DriverRecord;
        class SessionRecord;

    }

    namespace Detector {

        class LapFinished final : public Processor::Detector::Interface {

            public:
            // Default constructor
            LapFinished() = default;

            // Default destructor
            ~LapFinished() = default;

            // Returns the identifying type of this detector
            const Processor::Detector::Type GetType() const override;

            // Initializes the session record, forgoing the worker thread as it is not necessary
            void Init(Processor::Data::SessionRecord* sessionRecord,
                std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords) override final;

            // Compares a new completed lap with the current session best,
            // returning true and preparing the packet if this lap is indeed the session best
            bool checkFastestInSession(const Processor::Data::LapInfo& finishedLap);

            // Prepares a packet for a newly-finished lap
            void addFinishedLapInfo(const Processor::Data::LapInfo& finishedLap, const Lap::Internal::InfoType infoType);

            private:
            // Main execution function (does nothing)
            void Exec() override final {};

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_LAP_FINISHED_H_