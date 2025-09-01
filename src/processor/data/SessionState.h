#ifndef PROCESSOR_DATA_INCLUDE_SESSION_STATE_H_
#define PROCESSOR_DATA_INCLUDE_SESSION_STATE_H_

#include <cstdint>
#include <map>
#include "data/internal/Participant.h"
#include "holders/LapInfo.h"



namespace Processor {

    namespace Data {

        class SessionRecord;

        class SessionState {

            public:
            // Default constructor
            SessionState(Processor::Data::SessionRecord* parent);

            // Destructor
            ~SessionState();

            // Initializes the driver tracker
            void Init(const std::map<const uint8_t, bool>& participants);

            // Checks if a newly-finished lap is a new fastest lap for the current session
            bool evaluateCompletedLap(const Processor::Data::LapInfo& finishedLap);

            // Updates the internal tracking of the status of the drivers in the race, to determine when the session has finished
            // Returns true only once, at the cycle in which all drivers are noted to have completed the race
            bool updateDriverStatus(const uint8_t driverID, const bool completeness);

            // Exposes the session fastest lap data
            const Processor::Data::LapInfo& fastestLap() const;

            private:
            // Pointer to the session record holding this state
            const Processor::Data::SessionRecord* const m_parentRecord;

            // Denotes whether ALL the drivers have a finished state (DNF, DSQ or FinishedSession)
            bool m_sessionCompleteness;

            // Records the fastest lap of the current session
            Processor::Data::LapInfo m_fastestLap;

            // Map to track the finished status of the session, second element is true if a driver's lap entries have been completed
            std::map<const uint8_t, bool> m_driverTracker;

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_SESSION_STATE_H_