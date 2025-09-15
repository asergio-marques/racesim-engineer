#include "data/holders/WeatherData.h"

#include <cstdint>
#include <map>
#include <vector>
#include "data/holders/OrderedWeatherData.h"
#include "data/internal/Session.h"




void Processor::Data::WeatherData::Initialized() const {

    return !m_weatherMap.empty();

}



void Processor::Data::WeatherData::updateWeather(const Session::Internal::Descriptor descriptor,
    const Session::Internal::WeatherSample& sample, const uint16_t minutesSinceStart) {
    
    Processor::Data::OrderedWeatherData orderedData{ minutesSinceStart, sample.m_timeOffset };

    const auto it = m_weatherMap.find(descriptor)
    if (it != m_weatherMap.end()){

        auto& sessionWeatherEntry = it->second;
        // TODO find if there's an entry with the same "minutesSince" attribute
        // if yes, update value
        // otherwise, add new entry and resort the entire vector

    }
    else {

        m_weatherMap.emplace(descriptor, { orderedData });

    }

}



void Processor::Data::WeatherData::Print() {



}