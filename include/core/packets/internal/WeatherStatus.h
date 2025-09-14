#ifndef PACKETS_INTERNAL_INCLUDE_WEATHER_STATUS_H_
#define PACKETS_INTERNAL_INCLUDE_WEATHER_STATUS_H_

#include <cstdint>
#include <map>
#include <vector>
#include "data/internal/Session.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



namespace Packet {

    namespace Internal {

        class WeatherStatus : public Packet::Internal::Interface {

            public:
            // Packet constructor
            WeatherStatus(const uint64_t timestamp);

            // Destructor
            virtual ~WeatherStatus() = default;

            // Type identifier for the packet
            const Packet::Internal::Type packetType() const override final;

            // Adds grid position data into the packet
            void InsertData(Session::Internal::WeatherSample data);

            // Retrieve grid position data from the packet
            const std::vector<Session::Internal::WeatherSample>& GetData(Session::Internal::TypeDetail session) const;

            private:
            // Map with weather samples organized in chronological order, per session type
            std::map<Session::Internal::TypeDetail, std::vector<Session::Internal::WeatherSample>> m_weatherSamples;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_WEATHER_H_