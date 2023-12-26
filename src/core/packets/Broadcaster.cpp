#include "packets/Broadcaster.h"

#include <list>
#include "packets/Subscriber.h"



void Packet::Broadcaster::Subscribe(Packet::Subscriber* subscriber) {

    if (subscriber) {

        m_subscribers.push_back(subscriber);

    }

}



void Packet::Broadcaster::Broadcast(Packet::IPacket* packet) {

    if (packet) {

        // deletion of packet will be handled via shared_ptr
        const std::shared_ptr<Packet::IPacket> shared_packet(packet);
        for (auto subscriber : m_subscribers) {

            if (subscriber) subscriber->OnPacketBroadcast(shared_packet);

        }

    }

}