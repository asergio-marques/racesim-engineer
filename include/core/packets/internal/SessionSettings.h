#ifndef PACKETS_INTERNAL_INCLUDE_SESSION_SETTINGS_H_
#define PACKETS_INTERNAL_INCLUDE_SESSION_SETTINGS_H_

#include "data/internal/Session.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



namespace Packet {

    namespace Internal {

        struct SessionSettings : public Packet::Internal::Interface {

            public:
            // Packet interface constructor
            SessionSettings(const uint64_t timestamp, const Session::Internal::TrackInfo track, const Session::Internal::Settings settings);

            // Destructor
            virtual ~SessionSettings() = default;

            // Type identifier for the packet
            const Packet::Internal::Type packetType() const override final;

            // Holds information on the track this session is taking place at
            const Session::Internal::TrackInfo m_track;

            // Holds information about the characteristics of session taking place
            const Session::Internal::Settings m_settings;
        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_SESSION_SETTINGS_H_