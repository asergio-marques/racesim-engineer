#ifndef PROCESSOR_INCLUDE_IFACADE_H_
#define PROCESSOR_INCLUDE_IFACADE_H_

#include "packets/game/Broadcaster.h"
#include "packets/game/Subscriber.h"




namespace Processor {

    class IFacade : public Packet::Game::Broadcaster, public Packet::Game::Subscriber {

        public:
            IFacade() = default;
            virtual ~IFacade() = default;

    };

}

#endif // PROCESSOR_INCLUDE_IFACADE_H_