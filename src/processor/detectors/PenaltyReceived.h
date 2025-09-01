#ifndef PROCESSOR_DETECTOR_INCLUDE_PENALTY_RECEIVED_H_
#define PROCESSOR_DETECTOR_INCLUDE_PENALTY_RECEIVED_H_

#include "detectors/Interface.h"
#include "detectors/Type.h"



namespace Processor {

    namespace Data {

        class DriverRecord;
        class SessionRecord;

    }

    namespace Detector {

        class PenaltyReceived final : public Processor::Detector::Interface {

            public:
            // Default constructor
            PenaltyReceived() = default;

            // Default destructor
            ~PenaltyReceived() = default;

            // Returns the identifying type of this detector
            const Processor::Detector::Type GetType() const override;

            // Initializes the session record, forgoing the worker thread as it is not necessary
            void Init(Processor::Data::SessionRecord* sessionRecord,
                std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords) override final;

            // Interface function to create new packets for communicating changes to the UI
            void AddWarnPenChange(const int8_t id, const int8_t diffWarns,
                const int8_t diffTrackLims, const int32_t diffTimePens,
                const int8_t diffStopGo, const int8_t diffDriveThrough);

            private:
            // Main execution function (does nothing)
            void Exec() override final {};

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_PENALTY_RECEIVED_H_