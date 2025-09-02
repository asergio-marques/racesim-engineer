#ifndef PACKETS_EVENT_INCLUDE_TYRE_CHANGED_H_
#define PACKETS_EVENT_INCLUDE_TYRE_CHANGED_H_

#include <cstdint>
#include <string>
#include "data/internal/TyreData.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



namespace Packet {

    namespace Event {

        struct TyreChanged : public Packet::Event::Interface {

            public:
            // Packet interface constructor
            TyreChanged(const bool isPlayer, const std::string fullName, const uint8_t currentPosition);

            // Destructor
            virtual ~TyreChanged() = default;

            // Type identifier for the packet
            const Packet::Event::Type packetType() const override final;

            // Index for this participant
            uint8_t m_index;

            // Info for the new tyres
            Tyre::Internal::Data m_tyreInfo;

        };

    }

}

#endif  //  PACKETS_EVENT_INCLUDE_TYRE_CHANGED_H_