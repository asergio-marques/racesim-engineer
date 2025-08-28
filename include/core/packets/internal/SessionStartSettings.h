#ifndef PACKETS_INTERNAL_INCLUDE_SESSION_START_SETTINGS_H_
#define PACKETS_INTERNAL_INCLUDE_SESSION_START_SETTINGS_H_


#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



namespace Packet {

    namespace Internal {

        struct SessionStartSettings : public Packet::Internal::Interface {

            struct Data {

                public:
                // Constructor
                Data();

            };
            public:
            // Packet interface constructor
            SessionStartSettings(const uint64_t timestamp);

            // Destructor
            virtual ~SessionStartSettings() = default;

            // Type identifier for the packet
            const Packet::Internal::Type packetType() const override final;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_SESSION_START_SETTINGS_H_