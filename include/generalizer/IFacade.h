#ifndef GENERALIZER_INCLUDE_IFACADE_H_
#define GENERALIZER_INCLUDE_IFACADE_H_

#include "packets/internal/Broadcaster.h"
#include "packets/game/Subscriber.h"




namespace Generalizer {

    class IFacade : public Packet::Game::Subscriber {

        public:
        IFacade() = default;
        virtual ~IFacade() = default;

        virtual Packet::Internal::Broadcaster* exposeBroadcasterInterface() = 0;

    };

}

#endif // GENERALIZER_INCLUDE_IFACADE_H_