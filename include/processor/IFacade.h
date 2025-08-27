#ifndef PROCESSOR_INCLUDE_IFACADE_H_
#define PROCESSOR_INCLUDE_IFACADE_H_

#include <string>
#include "packets/event/Broadcaster.h"
#include "packets/internal/Subscriber.h"



namespace Presenter {

    class ICompFacade;

}

namespace Processor {

    class IFacade : public Packet::Internal::Subscriber, public Packet::Event::Broadcaster {

        public:
            IFacade() = default;
            virtual ~IFacade() = default;
            virtual void Init(Presenter::ICompFacade* presenter) = 0;
            virtual bool ExportCurrentRaceData(std::string path) = 0;

    };

}

#endif // PROCESSOR_INCLUDE_IFACADE_H_