#ifndef PROCESSOR_DATA_INCLUDE_WARNING_PENALTY_DATA_H_
#define PROCESSOR_DATA_INCLUDE_WARNING_PENALTY_DATA_H_

#include <cstdint>



namespace Processor {

    namespace Detector {

        class Interface;
        class WarningPenalty;

    }

    namespace Data {

        class WarningPenaltyData {

            public:
            WarningPenaltyData() = default;

            ~WarningPenaltyData() = default;

            // Add relevant detectors to then be called when relevant
            void installDetector(Processor::Detector::Interface* detector);

            // Alter the status of warnings and penalties, and feed it to the detector
            void updateWarningPenalties(const int8_t id, const uint8_t totalWarnings,
                const uint8_t trackLimitWarnings, const uint16_t timePenalties,
                const uint8_t stopGoPens, const uint8_t driveThroughPens);

            private:
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

            // Pointer to the penalty & warning detector currently installed
            Processor::Detector::WarningPenalty* m_installedPenWarnDetector;

        };

    }

}

#endif //  PROCESSOR_DATA_INCLUDE_WARNING_PENALTY_DATA_H_