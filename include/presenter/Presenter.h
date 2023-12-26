#ifndef PRESENTER_INCLUDE_PRESENTER_H_
#define PRESENTER_INCLUDE_PRESENTER_H_

#include <memory>
#include "packets/Subscriber.h"



namespace Presenter {

    class Presenter : public Packet::Subscriber {

        public:
            Presenter() = default;
            virtual ~Presenter() = default;
            virtual void OnPacketBroadcast(const std::shared_ptr<Packet::IPacket> packet) override final;

    };

}

#endif // PRESENTER_INCLUDE_PRESENTER_H_