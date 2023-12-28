#ifndef PACKETS_GAME_INCLUDE_BROADCASTER_H_
#define PACKETS_GAME_INCLUDE_BROADCASTER_H_

#include <list>



namespace Packet {

    namespace Game {

        class Interface;
        class Subscriber;

        class Broadcaster {

            public:
            Broadcaster() = default;
            virtual ~Broadcaster() = default;
            virtual void Subscribe(Packet::Game::Subscriber* subscriber);

            protected:
            // General function to divulge packet information to all subscribers
            void Broadcast(Packet::Game::Interface* packet);

            // Container for all the subscribers that will receive new packets
            std::list<Packet::Game::Subscriber*> m_subscribers;

        };

    }

}

#endif // PACKETS_GAME_INCLUDE_BROADCASTER_H_