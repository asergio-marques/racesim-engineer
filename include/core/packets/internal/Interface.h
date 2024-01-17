#ifndef PACKETS_INTERNAL_INCLUDE_INTERFACE_H_
#define PACKETS_INTERNAL_INCLUDE_INTERFACE_H_

#include <cstdint>
#include "packets/internal/Type.h"



namespace Packet {

    namespace Internal {

        class Interface {

            public:
            // Packet interface constructor
            Interface(const uint64_t timestamp) :
                m_timestamp(timestamp) {

            }

            // Destructor
            virtual ~Interface() = default;

            virtual const Packet::Internal::Type packetType() const = 0;
            virtual inline const bool isProcessed() const { return m_processed; }
            virtual inline void markAsProcessed() { m_processed = true; }
            const uint64_t m_timestamp;

            private:
            bool m_processed = false;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_INTERFACE_H_