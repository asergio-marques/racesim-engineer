#ifndef PROCESSOR_DATA_INCLUDE_POSITION_TIMING_DATA_H_
#define PROCESSOR_DATA_INCLUDE_POSITION_TIMING_DATA_H_

#include <cstdint>
#include "data/internal/Participant.h"


namespace Processor {

    namespace Detector {

        class ParticipantStatusChanged;
        class Interface;
        class Overtake;

    }

    namespace Data {

        class PositionTimingData {

            public:
            // Constructor
            PositionTimingData();

            ~PositionTimingData() = default;

            // Add relevant detectors to then be called when relevant
            bool installDetector(Processor::Detector::Interface* detector);

            // Validates the internal information and returns true if it meets the conditions for the start of a session
            const bool Initialized() const;

            // Alter the status of the driver itself in the session, and feed it to the detector
            void updateStatus(const uint8_t id, const Participant::Internal::Status status);

            // Set the initial grid position of the driver at the start of the session
            void setGridPosition(const uint8_t currentPosition);

            // Exposes the initial grid position of the driver at the start of the session
            const uint8_t getGridPosition() const;

            // Alter the position in this driver state, and feed it to the detector
            void updateCurrentPosition(const uint8_t id, const uint8_t currentPosition);

            // Denotes whether this driver has finished all his laps, or can no longer continue
            const bool isFinishedStatus() const;

            private:
            // Whether the grid position for this vehicle has been initialized or not
            bool m_isGridPositionSet;

            // Grid position for this vehicle
            uint8_t m_gridPosition;

            // Current position for this vehicle
            uint8_t m_currentPosition;

            // Status of the vehicle
            Participant::Internal::Status m_status;

            // Pointer to the overtake detector currently installed
            Processor::Detector::Overtake* m_installedOvertakeDetector;

            // Pointer to the status change detector currently installed
            Processor::Detector::ParticipantStatusChanged* m_installedStatusDetector;

        };

    }

}

#endif //  PROCESSOR_DATA_INCLUDE_POSITION_TIMING_DATA_H_