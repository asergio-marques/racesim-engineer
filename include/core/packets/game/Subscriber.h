#ifndef PACKETS_GAME_INCLUDE_SUBSCRIBER_H_
#define PACKETS_GAME_INCLUDE_SUBSCRIBER_H_

#include <memory>



namespace Packet {

    namespace Game {

        class Interface;

        class Subscriber {

            public:
            Subscriber() = default;
            virtual ~Subscriber() = default;
            virtual void OnPacketBroadcast(Packet::Game::Interface* packet) = 0;

        };

    }

}

#endif // PACKETS_GAME_INCLUDE_SUBSCRIBER_H_