#ifndef PROCESSOR_INCLUDE_IFACADE_H_
#define PROCESSOR_INCLUDE_IFACADE_H_

#include "packets/internal/Broadcaster.h"
#include "packets/internal/Subscriber.h"




namespace Processor {

    class IFacade : public Packet::Internal::Broadcaster, public Packet::Internal::Subscriber {

        public:
            IFacade() = default;
            virtual ~IFacade() = default;

    };

}

#endif // PROCESSOR_INCLUDE_IFACADE_H_