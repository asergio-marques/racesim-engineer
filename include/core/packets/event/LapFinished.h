#ifndef PACKETS_EVENT_INCLUDE_LAP_FINISHED_H_
#define PACKETS_EVENT_INCLUDE_LAP_FINISHED_H_

#include <cstdint>
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



namespace Packet {

    namespace Event {

        struct LapFinished : public Packet::Event::Interface {

            public:
            // Packet interface constructor
            LapFinished(const bool isPlayer, const std::string fullName, const uint8_t currentPosition);

            // Destructor
            virtual ~LapFinished() = default;

            // Type identifier for the packet
            const Packet::Event::Type packetType() const override final;

            // Index for this participant
            uint8_t m_index;

            // Time for this newly-finished lap
            Lap::Internal::Time m_lapTime;

            // Type of lap info this corresponds to
            Lap::Internal::InfoType m_infoType;

        };

    }

}

#endif  //  PACKETS_EVENT_INCLUDE_LAP_FINISHED_H_