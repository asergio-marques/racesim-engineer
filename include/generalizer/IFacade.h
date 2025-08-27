#ifndef GENERALIZER_INCLUDE_IFACADE_H_
#define GENERALIZER_INCLUDE_IFACADE_H_

#include "packets/game/Subscriber.h"
#include "packets/internal/Broadcaster.h"




namespace Packet {

    namespace Internal {

        class Broadcaster;

    }

}

namespace Generalizer {

    class IFacade : public Packet::Game::Subscriber, public Packet::Internal::Broadcaster {

        public:
        IFacade() = default;
        virtual ~IFacade() = default;

        virtual Packet::Internal::Broadcaster* exposeBroadcasterInterface() = 0;

    };

}

#endif // GENERALIZER_INCLUDE_IFACADE_H_