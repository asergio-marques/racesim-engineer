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
            TyreChanged();

            // Destructor
            virtual ~TyreChanged() = default;

            // Type identifier for the packet
            const Packet::Event::Type packetType() const override final;

            // Index for this participant
            uint8_t m_index;

            // Full name of this participant
            std::string m_fullName;

            // Position of this participant at the time of the tyre change
            uint8_t m_position;

            // Info for the new tyres
            Tyre::Internal::Data m_tyreInfo;

        };

    }

}

#endif  //  PACKETS_EVENT_INCLUDE_TYRE_CHANGED_H_