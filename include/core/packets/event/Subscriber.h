#ifndef PACKETS_EVENT_INCLUDE_SUBSCRIBER_H_
#define PACKETS_EVENT_INCLUDE_SUBSCRIBER_H_

#include <vector>



namespace Packet {

    namespace Event {

        class Interface;

        class Subscriber {

            public:
            // Default constructor
            Subscriber() = default;

            // Default destructor
            virtual ~Subscriber() = default;

            // Overriddable function that handles all incoming packets, to be overriden
            // by derived classes
            virtual void OnPacketBundleBroadcast(std::vector<Packet::Event::Interface*> packet) = 0;

        };

    }

}

#endif // PACKETS_EVENT_INCLUDE_SUBSCRIBER_H_