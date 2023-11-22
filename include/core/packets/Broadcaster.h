#ifndef PACKET_INCLUDE_BROADCASTER_H_
#define PACKET_INCLUDE_BROADCASTER_H_

#include <list>



namespace Packet {

    class IPacket;
    class Subscriber;

    class Broadcaster {

        public:
            Broadcaster() = default;
            virtual ~Broadcaster() = default;
            virtual void Subscribe(Packet::Subscriber* subscriber);

        protected:
            // General function to divulge packet information to all subscribers
            void Broadcast(Packet::IPacket* packet);

            // Container for all the subscribers that will receive new packets
            std::list<Packet::Subscriber*> m_subscribers;

    };

}

#endif // PACKET_INCLUDE_BROADCASTER_H_