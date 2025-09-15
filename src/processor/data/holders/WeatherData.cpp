#include "data/holders/WeatherData.h"

#include <cstdint>
#include <iostream>
#include <map>
#include <string>
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

    // assume everything is already ordered
    for (const auto& entry : m_weatherMap) {
        
        const auto session = entry.first;
        const auto weatherList = entry.second;
        
        std::string formatString = "";
        switch (session.m_roundType) {

            case Session::Internal::RoundDetail::NotApplicable:
                formatString = "";
                break;

            case Session::Internal::RoundDetail::Feature:
                formatString = "";
                break;

            case Session::Internal::RoundDetail::Sprint:
                formatString = "";
                break;

            default:
                formatString = "Unknown";

        }
        std::string sessionString;
        switch (session.m_sessionType) {

            case Session::Internal::TypeDetail::TimeTrial:
                sessionString = "TT";
                break;

            case Session::Internal::TypeDetail::FreePracticeSingle:
                sessionString = "FP";
                break;

            case Session::Internal::TypeDetail::FreePractice1:
                sessionString = "FP 1";
                break;

            case Session::Internal::TypeDetail::FreePractice2:
                sessionString = "FP 2";
                break;

            case Session::Internal::TypeDetail::FreePractice3:
                sessionString = "FP 3";
                break;

            case Session::Internal::TypeDetail::LapLimitQualifying:
                sessionString = formatString + " One-Shot Quali";
                break;

            case Session::Internal::TypeDetail::QualifyingSingleSession:
                sessionString = formatString + " Quali";
                break;

            case Session::Internal::TypeDetail::QualifyingSession1:
                sessionString = formatString + " Quali 1";
                break;

            case Session::Internal::TypeDetail::QualifyingSession2:
                sessionString = formatString + " Quali 2";
                break;

            case Session::Internal::TypeDetail::QualifyingSession3:
                sessionString = formatString + " Quali 3";
                break;

            case Session::Internal::TypeDetail::Race:
                sessionString = formatString + " Race";
                break;
            
            default:
                sessionString = "Unknown";

        }
        for (const auto& data : weatherList) {

            std::string weatherType = "";

            switch (data.m_sample.m_overall) {

                    case Session::Internal::WeatherType::Clear:
                        weatherType = "Clear";
                        break;

                    case Session::Internal::WeatherType::Cloudy:
                        weatherType = "Cloudy";
                        break;

                    case Session::Internal::WeatherType::Overcast:
                        weatherType = "Overcast";
                        break;

                    case Session::Internal::WeatherType::LightRain:
                        weatherType = "Wet";
                        break;
                        
                    case Session::Internal::WeatherType::HeavyRain:
                        weatherType = "Very Wet";
                        break;

                    case Session::Internal::WeatherType::RainWithLightning:
                        weatherType = "Thunderstorm";
                        break;

            }

            std::cout << "| " << sessionString << " | "
            << std::to_string(data.m_minutesSinceStart) << " mins | "
            << weatherType << " | "
            << std::to_string(data.m_sample.m_rainPercentage) << "% rain | "
            << std::to_string(data.m_sample.m_trackTemp) << "ºC track temp | "
            << std::to_string(data.m_sample.m_airTemp) << "ºC air temp | "
            << std::endl;

        }

    }

}