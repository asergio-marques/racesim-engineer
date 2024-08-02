#ifndef PROCESSOR_DATA_INCLUDE_POSITION_TIMING_DATA_H_
#define PROCESSOR_DATA_INCLUDE_POSITION_TIMING_DATA_H_

#include <cstdint>
#include "data/internal/Participant.h"


namespace Processor {

    namespace Data {

        struct PositionTimingData {

            // Constructor
            PositionTimingData(const uint8_t startingPosition) :
                m_currentPosition(startingPosition),
                m_startingPosition(startingPosition),
                m_status(Participant::Internal::Status::InvalidUnknown) {}

            // Starting position for this vehicle
            const uint8_t m_startingPosition;

            // Current position for this vehicle
            uint8_t m_currentPosition;

            // Status of the vehicle
            Participant::Internal::Status m_status;

        };

    }

}

#endif //  PROCESSOR_DATA_INCLUDE_POSITION_TIMING_DATA_H_