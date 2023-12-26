#ifndef PROCESSOR_INCLUDE_IFACADE_H_
#define PROCESSOR_INCLUDE_IFACADE_H_

#include "packets/Broadcaster.h"
#include "packets/Subscriber.h"




namespace Processor {

    class IFacade : public Packet::Broadcaster, public Packet::Subscriber {

        public:
            IFacade() = default;
            virtual ~IFacade() = default;

    };

}

#endif // PROCESSOR_INCLUDE_IFACADE_H_