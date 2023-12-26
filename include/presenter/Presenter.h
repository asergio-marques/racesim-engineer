#ifndef PRESENTER_INCLUDE_PRESENTER_H_
#define PRESENTER_INCLUDE_PRESENTER_H_

#include <memory>
#include "packets/game/Subscriber.h"



namespace Presenter {

    class Presenter : public Packet::Game::Subscriber {

        public:
            Presenter() = default;
            virtual ~Presenter() = default;
            virtual void OnPacketBroadcast(const std::shared_ptr<Packet::Game::Interface> packet) override final;

    };

}

#endif // PRESENTER_INCLUDE_PRESENTER_H_