#ifndef PROCESSOR_DATA_INCLUDE_SESSION_STATE_H_
#define PROCESSOR_DATA_INCLUDE_SESSION_STATE_H_

#include <cstdint>
#include <map>
#include "data/internal/Participant.h"
#include "data/holders/LapInfo.h"
#include "data/holders/WeatherData.h"



namespace Processor {

    namespace Data {

        class SessionRecord;

        class SessionState {

            public:
            // Default constructor
            SessionState(Processor::Data::SessionRecord* parent);

            // Destructor
            ~SessionState();

            // Marks the state of the current session as finalized
            void sessionFinalized();

            // Validates the internal information and returns true if it meets the conditions for the start of a session
            bool Initialized();

            // Checks if a newly-finished lap is a new fastest lap for the current session
            bool evaluateCompletedLap(const Processor::Data::LapInfo& finishedLap);

            // Updates the weather data for this session (and other associated sessions) with further samples
            void updateWeather(const Session::Internal::Descriptor& descriptor,
                const Session::Internal::WeatherSample& sample, const uint16_t minutesSinceStart);

            // Exposes the session weather data
            const Processor::Data::WeatherData& weather() const;

            // Exposes the session fastest lap data
            const Processor::Data::LapInfo& fastestLap() const;

            private:
            // Pointer to the session record holding this state
            const Processor::Data::SessionRecord* const m_parentRecord;

            // Whether this session is currently ongoing
            bool m_running;

            // Holder of all weather information for this lobby
            Processor::Data::WeatherData m_weather;

            // Records the fastest lap of the current session
            Processor::Data::LapInfo m_fastestLap;

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_SESSION_STATE_H_