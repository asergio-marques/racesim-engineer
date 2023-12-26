#ifndef PACKET_INCLUDE_SUBSCRIBER_H_
#define PACKET_INCLUDE_SUBSCRIBER_H_

#include <memory>



namespace Packet {

    class IPacket;

    class Subscriber {

        public:
            Subscriber() = default;
            virtual ~Subscriber() = default;
            virtual void OnPacketBroadcast(const std::shared_ptr<Packet::IPacket> packet) = 0;

    };

}

#endif // PACKET_INCLUDE_SUBSCRIBER_H_