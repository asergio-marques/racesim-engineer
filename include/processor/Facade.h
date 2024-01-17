#ifndef PROCESSOR_INCLUDE_FACADE_H_
#define PROCESSOR_INCLUDE_FACADE_H_

#include <vector>
#include "IFacade.h"


namespace Processor {

    namespace Data {

        class Databank;

    }

    namespace Detector {

        class Interface;

    }

    class Facade : public Processor::IFacade {

        public:
            Facade();
            virtual ~Facade();
            virtual void OnPacketBroadcast(Packet::Internal::Interface* packet) override final;

        private:
            Processor::Data::Databank* const m_databank;
            std::vector<Processor::Detector::Interface*> m_detectors;

    };

}

#endif // PROCESSOR_INCLUDE_FACADE_H_