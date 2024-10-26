#ifndef PACKETS_INTERNAL_INCLUDE_SESSION_START_H_
#define PACKETS_INTERNAL_INCLUDE_SESSION_START_H_

#include <cstdint>
#include "data/internal/Session.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"


namespace Packet {

    namespace Internal {

        struct SessionStart : public Packet::Internal::Interface {

            public:
            // Packet interface constructor
            SessionStart(const uint64_t timestamp, const Session::Internal::Type& sessionType);

            // Destructor
            virtual ~SessionStart() = default;

            // Type identifier for the packet
            const Packet::Internal::Type packetType() const override final;

            // The type of the session that has begun
            Session::Internal::Type m_sessionType;

            // The track at which the session is taking place
            Session::Internal::Track m_sessionTrack;

            // Total distance for a single lap at the track, if available (meters)
            float_t m_lapDistanceTotal;

            // Distance of Sector 1, if available (meters)
            float_t m_sector1Distance;

            // Distance of Sector 2, if available (meters)
            float_t m_sector2Distance;

            // Distance of Sector 3, if available (meters)
            float_t m_sector3Distance;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_SESSION_START_H_