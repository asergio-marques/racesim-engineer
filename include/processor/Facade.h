#ifndef PROCESSOR_INCLUDE_FACADE_H_
#define PROCESSOR_INCLUDE_FACADE_H_

#include <thread>
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
            void Exec();

        private:
            Processor::Data::Databank* const m_databank;
            std::vector<Processor::Detector::Interface*> m_detectors;
            std::thread m_execThread;

    };

}

#endif // PROCESSOR_INCLUDE_FACADE_H_