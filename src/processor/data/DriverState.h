#ifndef PROCESSOR_DATA_INCLUDE_DRIVER_STATE_H_
#define PROCESSOR_DATA_INCLUDE_DRIVER_STATE_H_

#include <cstdint>
#include <vector>



namespace Processor {
    
    namespace Detector {

        class Interface;
        class Overtake;

    }

    namespace Data {

        class DriverState {

            public:

            DriverState(const uint8_t id, const uint8_t startingPosition);
            ~DriverState();
            void installDetector(const Processor::Detector::Interface* detector);
            void updateCurrentPosition(const uint8_t currentPosition);
            const uint8_t getCurrentPosition() const;

            private:
            const uint8_t m_id;
            uint8_t m_currentPosition;
            const uint8_t m_startingPosition;
            const Processor::Detector::Overtake* m_installedOvertakeDetector;


        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_DRIVER_STATE_H_