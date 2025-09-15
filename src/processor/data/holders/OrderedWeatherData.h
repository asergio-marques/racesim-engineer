#ifndef PROCESSOR_DATA_INCLUDE_ORDERED_WEATHER_DATA_H_
#define PROCESSOR_DATA_INCLUDE_ORDERED_WEATHER_DATA_H_

#include <cstdint>
#include "data/internal/Session.h"




namespace Processor {

    namespace Data {

        struct OrderedWeatherData {
            OrderedWeatherData(const uint16_t minutesSinceStart, const uint16_t m_timeOffset);
            OrderedWeatherData(const OrderedWeatherData& other) = default;
            OrderedWeatherData& operator=(const OrderedWeatherData& other);
            bool operator==(const OrderedWeatherData& other) const;
            bool operator!=(const OrderedWeatherData& other) const;
            bool operator>(const OrderedWeatherData& other) const;
            bool operator<(const OrderedWeatherData& other) const;
            bool operator>=(const OrderedWeatherData& other) const;
            bool operator<=(const OrderedWeatherData& other) const;

            // Notes how many minutes since the start of the session to which this sample pertains will this weather occur
            const uint16_t m_minutesSinceStart;

            // Weather information
            Session::Internal::WeatherSample m_sample;

        };

    }

}

#endif //  PROCESSOR_DATA_INCLUDE_LAP_INFO_H_