#ifndef PACKETS_EVENT_INCLUDE_INTERFACE_H_
#define PACKETS_EVENT_INCLUDE_INTERFACE_H_

#include <cstdint>
#include "packets/event/Type.h"



namespace Packet {

    namespace Event {

        class Interface {

            public:
            // Packet interface constructor
            Interface();

            // Destructor
            virtual ~Interface() = default;

            // Type identifier for the packet, to be overridden
            virtual const Packet::Event::Type packetType() const = 0;

            // Denotes if this packet has been fully processed and if it can be deleted
            virtual inline const bool isProcessed() const;

            // Marks this packet has having been fully processed
            virtual inline void markAsProcessed();

            private:
            // Whether the packet has been processed
            bool m_processed;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_INTERFACE_H_