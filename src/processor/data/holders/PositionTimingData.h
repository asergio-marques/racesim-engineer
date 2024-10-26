#ifndef PROCESSOR_DATA_INCLUDE_POSITION_TIMING_DATA_H_
#define PROCESSOR_DATA_INCLUDE_POSITION_TIMING_DATA_H_

#include <cstdint>
#include "data/internal/Participant.h"


namespace Processor {

    namespace Detector {

        class DriverStatus;
        class Interface;
        class Overtake;

    }

    namespace Data {

        class PositionTimingData {

            public:
            // Constructor
            PositionTimingData(const uint8_t startingPosition);

            ~PositionTimingData() = default;

            // Add relevant detectors to then be called when relevant
            void installDetector(Processor::Detector::Interface* detector);

            // Alter the status of the driver itself in the session, and feed it to the detector
            void updateStatus(const uint8_t id, const Participant::Internal::Status status);

            // Alter the position in this driver state, and feed it to the detector
            void updateCurrentPosition(const uint8_t id, const uint8_t currentPosition);

            private:
            // Starting position for this vehicle
            const uint8_t m_startingPosition;

            // Current position for this vehicle
            uint8_t m_currentPosition;

            // Status of the vehicle
            Participant::Internal::Status m_status;

            // Pointer to the overtake detector currently installed
            Processor::Detector::Overtake* m_installedOvertakeDetector;

            // Pointer to the status change detector currently installed
            Processor::Detector::DriverStatus* m_installedStatusDetector;

        };

    }

}

#endif //  PROCESSOR_DATA_INCLUDE_POSITION_TIMING_DATA_H_