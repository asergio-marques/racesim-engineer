#ifndef PACKETS_EVENT_INCLUDE_INTERFACE_H_
#define PACKETS_EVENT_INCLUDE_INTERFACE_H_

#include <cstdint>
#include "packets/internal/Type.h"



namespace Packet {

    namespace Event {

        class Interface {

            public:
            // Packet interface constructor
            Interface(const uint64_t timestamp);

            // Destructor
            virtual ~Interface() = default;

            // Type identifier for the packet, to be overridden
            virtual const Packet::Event::Type packetType() const = 0;

            // Denotes if this packet has been fully processed and if it can be deleted
            virtual inline const bool isProcessed() const;

            // Marks this packet has having been fully processed
            virtual inline void markAsProcessed();

            // Ingame timestamp that identifies the packet
            const uint64_t m_timestamp;

            private:
            // Whether the packet has been processed
            bool m_processed;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_INTERFACE_H_