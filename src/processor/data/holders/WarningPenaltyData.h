#ifndef PROCESSOR_DATA_INCLUDE_WARNING_PENALTY_DATA_H_
#define PROCESSOR_DATA_INCLUDE_WARNING_PENALTY_DATA_H_

#include <cstdint>



namespace Processor {

    namespace Data {

        struct WarningPenaltyData {

            // Number of warnings of all types issued
            uint8_t m_totalWarns;

            // Number of outstanding track limit warnings
            uint8_t m_numTrackLimits;

            // Time penalty (in millisseconds) to be added at the end of the session
            uint16_t m_timePenMS;

            // Number of stop-go penalties still to be served
            uint8_t m_numStopGo;

            // Number of drive-through penalties still to be served
            uint8_t m_numDriveThrough;

        };

    }

}

#endif //  PROCESSOR_DATA_INCLUDE_WARNING_PENALTY_DATA_H_