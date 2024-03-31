#ifndef PROCESSOR_DATA_INCLUDE_WARNING_PENALTY_DATA_H_
#define PROCESSOR_DATA_INCLUDE_WARNING_PENALTY_DATA_H_

#include <cstdint>



namespace Processor {

    namespace Data {

        struct WarningPenaltyData {

            // Number of warnings of all types issued
            const uint8_t m_totalWarns = 0;

            // Number of outstanding track limit warnings
            const uint8_t m_numTrackLimits = 0;

            // Time penalty (in millisseconds) to be added at the end of the session
            const uint16_t m_timePenMS = 0;

            // Number of stop-go penalties still to be served
            const uint8_t m_numStopGo = 0;

            // Number of drive-through penalties still to be served
            const uint8_t m_numDriveThrough = 0;

        };

    }

}

#endif //  PROCESSOR_DATA_INCLUDE_WARNING_PENALTY_DATA_H_