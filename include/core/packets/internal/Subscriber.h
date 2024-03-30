#ifndef PACKETS_INTERNAL_INCLUDE_SUBSCRIBER_H_
#define PACKETS_INTERNAL_INCLUDE_SUBSCRIBER_H_

#include <memory>



namespace Packet {

    namespace Internal {

        class Interface;

        class Subscriber {

            public:
            // Default constructor
            Subscriber() = default;

            // Default destructor
            virtual ~Subscriber() = default;

            // Overriddable function that handles all incoming packets, to be overriden
            // by derived classes
            virtual void OnPacketBroadcast(Packet::Internal::Interface* packet) = 0;

        };

    }

}

#endif // PACKETS_INTERNAL_INCLUDE_SUBSCRIBER_H_