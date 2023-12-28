#ifndef PACKETS_INTERNAL_INCLUDE_BROADCASTER_H_
#define PACKETS_INTERNAL_INCLUDE_BROADCASTER_H_

#include <list>



namespace Packet {

    namespace Internal {

        class Interface;
        class Subscriber;

        class Broadcaster {

            public:
            Broadcaster() = default;
            virtual ~Broadcaster() = default;
            virtual void Subscribe(Packet::Internal::Subscriber* subscriber);

            protected:
            // General function to divulge packet information to all subscribers
            void Broadcast(Packet::Internal::Interface* packet);

            // Container for all the subscribers that will receive new packets
            std::list<Packet::Internal::Subscriber*> m_subscribers;

        };

    }

}

#endif // PACKETS_INTERNAL_INCLUDE_BROADCASTER_H_