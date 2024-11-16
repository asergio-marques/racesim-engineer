#ifndef PROCESSOR_DATA_INCLUDE_SESSION_STATE_H_
#define PROCESSOR_DATA_INCLUDE_SESSION_STATE_H_

#include "holders/LapInfo.h"



namespace Processor {

    namespace Data {

        class SessionState {

            public:
            // Default constructor
            SessionState();

            // Destructor
            ~SessionState();

            // Checks if a newly-finished lap is a new fastest lap for the current session
            bool evaluateCompletedLap(const Processor::Data::LapInfo& finishedLap);

            // Exposes the session fastest lap data
            const Processor::Data::LapInfo& fastestLap() const;

            private:
            // Records the fastest lap of the current session
            Processor::Data::LapInfo m_fastestLap;

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_SESSION_STATE_H_