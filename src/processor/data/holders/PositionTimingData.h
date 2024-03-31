#ifndef PROCESSOR_DATA_INCLUDE_POSITION_TIMING_DATA_H_
#define PROCESSOR_DATA_INCLUDE_POSITION_TIMING_DATA_H_

#include <cstdint>



namespace Processor {

    namespace Data {

        struct PositionTimingData {

            // Constructor
            PositionTimingData(const uint8_t startingPosition) :
                m_currentPosition(startingPosition),
                m_startingPosition(startingPosition) {}

            // Starting position for this vehicle
            const uint8_t m_startingPosition;

            // Current position for this vehicle
            uint8_t m_currentPosition;

        };

    }

}

#endif //  PROCESSOR_DATA_INCLUDE_POSITION_TIMING_DATA_H_