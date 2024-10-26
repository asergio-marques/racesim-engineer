#ifndef PROCESSOR_DETECTOR_INCLUDE_DRIVER_STATUS_H_
#define PROCESSOR_DETECTOR_INCLUDE_DRIVER_STATUS_H_

#include <cstdint>
#include <vector>
#include "data/internal/Participant.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"



namespace Processor {

    namespace Detector {

        class DriverStatus final : public Processor::Detector::Interface {

            struct StatusChange {

                // ID of the vehicle with the changed status
                const uint8_t m_id;

                // New status for this vehicle
                const Participant::Internal::Status m_status;

            };

            public:
            // Default constructor
            DriverStatus() = default;

            // Default destructor
            ~DriverStatus() = default;

            // Returns the identifying type of this detector
            const Processor::Detector::Type GetType() const override;

            // Interface function to create new packets for communicating changes to the UI
            void AddStatusChange(const uint8_t id, const Participant::Internal::Status newStatus);

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_OVERTAKE_H_