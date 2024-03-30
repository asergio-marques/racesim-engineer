#ifndef PROCESSOR_DATA_INCLUDE_DRIVER_STATE_H_
#define PROCESSOR_DATA_INCLUDE_DRIVER_STATE_H_

#include <cstdint>



namespace Processor {
    
    namespace Detector {

        class Interface;
        class Overtake;

    }

    namespace Data {

        class DriverState {

            public:
            // Constructor
            DriverState(const uint8_t id, const uint8_t startingPosition);

            // Destructor
            ~DriverState();

            // Add relevant detectors to then be called when relevant
            void installDetector(Processor::Detector::Interface* detector);

            // Alter the position in this driver state, and feed it to the detector
            void updateCurrentPosition(const uint8_t currentPosition);

            private:
            // ID of the driver associated with this state
            const uint8_t m_id;

            // Current position for this vehicle
            uint8_t m_currentPosition;

            // Starting position for this vehicle
            const uint8_t m_startingPosition;

            // Pointer to the overtake detector currently installed
            Processor::Detector::Overtake* m_installedOvertakeDetector;


        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_DRIVER_STATE_H_