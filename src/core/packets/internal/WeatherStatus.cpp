#include "packets/internal/WeatherStatus.h"

#include <algorithm>
#include <cstdint>
#include <map>
#include <vector>
#include "data/internal/Session.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"




Packet::Internal::WeatherStatus::WeatherStatus(const uint64_t timestamp) :
    Packet::Internal::Interface(timestamp),
    m_weatherSamples() {

}



const Packet::Internal::Type Packet::Internal::WeatherStatus::packetType() const {

    return Packet::Internal::Type::WeatherStatus;

}



void Packet::Internal::WeatherStatus::InsertData(Session::Internal::WeatherSample data) {

    auto it = m_weatherSamples.find(data.m_sessionType);
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
        m_weatherSamples.emplace(data.m_sessionType, v);

    }

}



const std::vector<Session::Internal::WeatherSample>& Packet::Internal::WeatherStatus::GetData(Session::Internal::TypeDetail session) const {

    auto& it = m_weatherSamples.find(session);
    if (it != m_weatherSamples.end()) {

        return it->second;

    }

    return {};

}