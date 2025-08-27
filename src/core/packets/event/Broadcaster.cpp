#include "packets/Event/Broadcaster.h"

#include <list>
#include <vector>
#include "packets/Event/Subscriber.h"



void Packet::Event::Broadcaster::Subscribe(Packet::Event::Subscriber* subscriber) {

    if (subscriber) {

        m_subscribers.push_back(subscriber);

    }

}



void Packet::Event::Broadcaster::Broadcast(std::vector<Packet::Event::Interface*> packets) {

    if (!packets.empty()) {

        for (auto subscriber : m_subscribers) {

            if (subscriber) subscriber->OnPacketBundleBroadcast(packets);

        }

    }

}