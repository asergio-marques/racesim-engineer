#ifndef GENERALIZER_INCLUDE_FACADE_H_
#define GENERALIZER_INCLUDE_FACADE_H_

#include "IFacade.h"




namespace Generalizer {

    class Facade : public Generalizer::IFacade {

        public:
        Facade() = default;
        virtual ~Facade() = default;

        Packet::Internal::Broadcaster* exposeBroadcasterInterface() override;
        void OnPacketBroadcast(Packet::Game::Interface* packet) override;

    };

}

#endif // GENERALIZER_INCLUDE_FACADE_H_