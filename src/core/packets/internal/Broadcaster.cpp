#include "packets/internal/Broadcaster.h"

#include <list>
#include "packets/internal/Subscriber.h"



void Packet::Internal::Broadcaster::Subscribe(Packet::Internal::Subscriber* subscriber) {

    if (subscriber) {

        m_subscribers.push_back(subscriber);

    }

}



void Packet::Internal::Broadcaster::Broadcast(Packet::Internal::Interface* packet) {

    if (packet) {

        for (auto subscriber : m_subscribers) {

            if (subscriber) subscriber->OnPacketBroadcast(packet);

        }

    }

}