#include "packets/internal/Broadcaster.h"

#include <list>
#include <vector>
#include "packets/internal/Subscriber.h"



void Packet::Internal::Broadcaster::Subscribe(Packet::Internal::Subscriber* subscriber) {

    if (subscriber) {

        m_subscribers.push_back(subscriber);

    }

}



void Packet::Internal::Broadcaster::Broadcast(std::vector<Packet::Internal::Interface*> packets) {

    if (!packets.empty()) {

        for (auto subscriber : m_subscribers) {

            if (subscriber) subscriber->OnPacketBundleBroadcast(packets);

        }

    }

}