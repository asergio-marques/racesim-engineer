#include "packets/internal/WeatherStatus.h"

#include <algorithm>
#include <cstdint>
#include <map>
#include <vector>
#include "data/internal/Session.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"




Packet::Internal::WeatherStatus::WeatherStatus(const uint64_t timestamp, const Session::Internal::RoundDetail currentSessionFormat,
    const Session::Internal::TypeDetail currentSession, const uint16_t secondsSinceStart) :
    Packet::Internal::Interface(timestamp),
    m_currentSession(currentSessionFormat, currentSession),
    m_minutesSinceStart(std::floor(secondsSinceStart / 60)),
    m_weatherSamples() {

}



const Packet::Internal::Type Packet::Internal::WeatherStatus::packetType() const {

    return Packet::Internal::Type::WeatherStatus;

}



void Packet::Internal::WeatherStatus::InsertData(Session::Internal::WeatherSample data) {

    Session::Internal::Descriptor des{data.m_roundType, data.m_sessionType};
    auto it = m_weatherSamples.find(des);
    if (it != m_weatherSamples.end()) {

        auto& v = it->second;
        v.push_back(data);
        std::sort(v.begin(), v.end(), [](const Session::Internal::WeatherSample& a, const Session::Internal::WeatherSample& b) {

            return a.m_minutesSinceStart > b.m_minutesSinceStart;

        });

    }
    else {

        std::vector<Session::Internal::WeatherSample> v;
        v.push_back(data);
        m_weatherSamples.emplace(des, v);

    }

}



const std::vector<Session::Internal::Descriptor> Packet::Internal::WeatherStatus::GetSessions() const{

    std::vector<Session::Internal::Descriptor> temp;

    for (const auto& sample : m_weatherSamples) {
        
        bool found = false;

        if (std::find(temp.begin(), temp.end(), sample->first) != temp.end()) {

            found = true;

        }
        if (!found){

            temp.push_back(sample->first);

        }

    }

    return temp;

}



const std::vector<Session::Internal::WeatherSample>& Packet::Internal::WeatherStatus::GetData(Session::Internal::Descriptor descriptor) const {

    auto& it = m_weatherSamples.find(descriptor);
    if (it != m_weatherSamples.end()) {

        return it->second;

    }

    return {};

}