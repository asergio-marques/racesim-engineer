#ifndef PROCESSOR_DATA_INCLUDE_DRIVER_STATE_H_
#define PROCESSOR_DATA_INCLUDE_DRIVER_STATE_H_

#include <cstdint>



namespace Processor {

    namespace Data {

        class DriverState {

            public:
            DriverState(const uint8_t startingPosition);
            ~DriverState();

            private:
            uint8_t m_currentPosition;
            uint8_t m_startingPosition;

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_DRIVER_STATE_H_