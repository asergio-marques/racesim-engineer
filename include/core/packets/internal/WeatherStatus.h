#ifndef PACKETS_INTERNAL_INCLUDE_WEATHER_STATUS_H_
#define PACKETS_INTERNAL_INCLUDE_WEATHER_STATUS_H_

#include <cstdint>
#include <map>
#include <pair>
#include "data/internal/Session.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



namespace Packet {

    namespace Internal {

        class WeatherStatus : public Packet::Internal::Interface {

            public:
            // Packet constructor
            WeatherStatus(const uint64_t timestamp, const Session::Internal::RoundDetail currentSessionFormat, const Session::Internal::TypeDetail currentSession, const uint16_t secondsSinceStart);

            // Destructor
            virtual ~WeatherStatus() = default;

            // Type identifier for the packet
            const Packet::Internal::Type packetType() const override final;

            // Adds a weather sample into the packet
            void InsertData(Session::Internal::WeatherSample data);

            // Retrieve all the weather samples for a given format and session
            const std::vector<Session::Internal::WeatherSample>& GetData(Session::Internal::Descriptor descriptor) const;

            // Retrieve the session configurations for which samples are available in this packet
            const std::vector<Session::Internal::Descriptor> GetSessions() const;

            // Identifies the current session's format (e.g. sprint, feature) and type (e.g. quali, race)
            const Session::Internal::Descriptor m_currentSession;

            // Elapsed time since the start of the current session (minutes)
            const uint16_t m_minutesSinceStart;

            private:
            // Map with weather samples organized in chronological order, per session type
            std::map<Session::Internal::Descriptor, std::vector<Session::Internal::WeatherSample>> m_weatherSamples;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_WEATHER_H_