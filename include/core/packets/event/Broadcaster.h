#ifndef PACKETS_EVENT_INCLUDE_BROADCASTER_H_
#define PACKETS_EVENT_INCLUDE_BROADCASTER_H_

#include <list>
#include <vector>


namespace Packet {

    namespace Event {

        class Interface;
        class Subscriber;

        class Broadcaster {

            public:
            Broadcaster() = default;
            virtual ~Broadcaster() = default;
            virtual void Subscribe(Packet::Event::Subscriber* subscriber);

            protected:
            // General function to divulge packet information to all subscribers
            void Broadcast(std::vector<Packet::Event::Interface*> packets);

            // Container for all the subscribers that will receive new packets
            std::list<Packet::Event::Subscriber*> m_subscribers;

        };

    }

}

#endif // PACKETS_EVENT_INCLUDE_BROADCASTER_H_