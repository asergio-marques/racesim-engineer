#include "packets/game/Broadcaster.h"

#include <list>
#include "packets/game/Subscriber.h"



void Packet::Game::Broadcaster::Subscribe(Packet::Game::Subscriber* subscriber) {

    if (subscriber) {

        m_subscribers.push_back(subscriber);

    }

}



void Packet::Game::Broadcaster::Broadcast(Packet::Game::Interface* packet) {

    if (packet) {

        // deletion of packet will be handled via shared_ptr
        const std::shared_ptr<Packet::Game::Interface> shared_packet(packet);
        for (auto subscriber : m_subscribers) {

            if (subscriber) subscriber->OnPacketBroadcast(shared_packet);

        }

    }

}