#ifndef PACKETS_INTERNAL_INCLUDE_SUBSCRIBER_H_
#define PACKETS_INTERNAL_INCLUDE_SUBSCRIBER_H_

#include <memory>



namespace Packet {

    namespace Internal {

        class Interface;

        class Subscriber {

            public:
            Subscriber() = default;
            virtual ~Subscriber() = default;
            virtual void OnPacketBroadcast(Packet::Internal::Interface* packet) = 0;

        };

    }

}

#endif // PACKETS_INTERNAL_INCLUDE_SUBSCRIBER_H_