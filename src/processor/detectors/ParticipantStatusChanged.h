#ifndef PROCESSOR_DETECTOR_INCLUDE_PARTICIPANT_STATUS_CHANGED_H_
#define PROCESSOR_DETECTOR_INCLUDE_PARTICIPANT_STATUS_CHANGED_H_

#include <cstdint>
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

        class ParticipantStatusChanged final : public Processor::Detector::Interface {

            public:
            // Default constructor
            ParticipantStatusChanged() = default;

            // Default destructor
            ~ParticipantStatusChanged() = default;

            // Returns the identifying type of this detector
            const Processor::Detector::Type GetType() const override;

            // Initializes the session record, forgoing the worker thread as it is not necessary
            void Init(Processor::Data::SessionRecord* sessionRecord,
                std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords) override final;

            // Interface function to create new packets for communicating changes to the UI
            void AddStatusChange(const uint8_t id, const Participant::Internal::Status newStatus);

            private:
            // Main execution function (does nothing)
            void Exec() override final {};

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_PARTICIPANT_STATUS_CHANGED_H_