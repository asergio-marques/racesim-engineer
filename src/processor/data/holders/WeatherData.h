#ifndef PROCESSOR_DATA_INCLUDE_WEATHER_DATA_H_
#define PROCESSOR_DATA_INCLUDE_WEATHER_DATA_H_

#include <cstdint>
#include <map>
#include <vector>
#include "data/holders/OrderedWeatherData.h"
#include "data/internal/Session.h"




namespace Processor {

    namespace Data {

        class WeatherData {

            public:
            WeatherData() = default;

            ~WeatherData() = default;
            
            // Validates the internal information and returns true if it meets the conditions for the start of a session
            bool Initialized() const;

            // Updates the weather samples stored with new information
            void updateWeather(const Session::Internal::Descriptor& descriptor,
                const Session::Internal::WeatherSample& sample, const uint16_t minutesSinceStart);

            // TODO remove this once weather info is sent to the UI
            void Print(const Session::Internal::Descriptor& currentSession);

            private:
            // Format and type of the current session taking place, used to "locate" the current weather
            Session::Internal::Descriptor m_currentSession;

            // Container mapping each session type in the lobby to an ordered vector with the weather data
            std::map<Session::Internal::Descriptor, std::vector<Processor::Data::OrderedWeatherData>> m_weatherMap;
            


        };

    }

}

#endif //  PROCESSOR_DATA_INCLUDE_WEATHER_DATA_H_