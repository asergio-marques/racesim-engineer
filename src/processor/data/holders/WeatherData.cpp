#include "data/holders/WeatherData.h"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "data/holders/OrderedWeatherData.h"
#include "data/internal/Session.h"




bool Processor::Data::WeatherData::Initialized() const {

    return !m_weatherMap.empty();

}



void Processor::Data::WeatherData::updateWeather(const Session::Internal::Descriptor& descriptor,
    const Session::Internal::WeatherSample& sample, const uint16_t minutesSinceStart) {

    Processor::Data::OrderedWeatherData orderedData{ minutesSinceStart, sample.m_timeOffset };
    orderedData.m_sample = sample;

    const auto it = m_weatherMap.find(sample.m_descriptor);
    if (it != m_weatherMap.end()) {

        auto& sessionWeatherEntry = it->second;

        // find if there's an entry with the same "minutesSince" attribute
        // if there is, merely update the value
        // otherwise, add a new entry and resort the entire vector
        auto entry = std::find_if(sessionWeatherEntry.begin(), sessionWeatherEntry.end(),
            [&orderedData](const Processor::Data::OrderedWeatherData& entry) {

                return (entry.m_minutesSinceStart == orderedData.m_minutesSinceStart);

            });
        if (entry != sessionWeatherEntry.end()) {

            entry->m_sample.m_overall = sample.m_overall;
            entry->m_sample.m_airTemp = sample.m_airTemp;
            entry->m_sample.m_trackTemp = sample.m_trackTemp;
            entry->m_sample.m_humidity = sample.m_humidity;
            entry->m_sample.m_rain = sample.m_rain;
            entry->m_sample.m_windSpeed = sample.m_windSpeed;
            entry->m_sample.m_windDirection = sample.m_windDirection;

        }
        else {

            sessionWeatherEntry.push_back(orderedData);
            std::sort(sessionWeatherEntry.begin(), sessionWeatherEntry.end(),
                [](const Processor::Data::OrderedWeatherData& a, const Processor::Data::OrderedWeatherData& b) {

                    return a.m_minutesSinceStart < b.m_minutesSinceStart;

            });

        }


    }
    else {

        std::vector<Processor::Data::OrderedWeatherData> v;
        v.push_back(orderedData);
        m_weatherMap.emplace(sample.m_descriptor, v);

    }

}



void Processor::Data::WeatherData::Print(const Session::Internal::Descriptor& currentSession) const {

    std::cout << "-----------------------------------------------------------------"
        "-------------------------------------------------------------------------" << std::endl;
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
                formatString = "Feature";
                break;

            case Session::Internal::RoundDetail::Sprint:
                formatString = "Sprint";
                break;

            default:
                formatString = "Unknown";

        }
        std::string sessionString = "";
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

                default:
                    weatherType = "Unknown";

            }

            std::string currentSeasonStartString = "";
            if ((session.m_roundType == currentSession.m_roundType) &&
                (session.m_sessionType == currentSession.m_sessionType) &&
                data.m_minutesSinceStart == 0) {

                currentSeasonStartString = "<== CURRENT!";

            }

            std::cout << "| " << sessionString << "\t| " <<
                std::to_string(data.m_minutesSinceStart) << " mins\t| " <<
                weatherType << "\t| " <<
                std::to_string(data.m_sample.m_rain) << "% rain\t| " <<
                std::to_string(data.m_sample.m_trackTemp) << "degC track temp\t| " <<
                std::to_string(data.m_sample.m_airTemp) << "degC air temp\t| " <<
                currentSeasonStartString << std::endl;

        }

    }
    
    std::cout << "-----------------------------------------------------------------"
        "-------------------------------------------------------------------------" << std::endl;

}