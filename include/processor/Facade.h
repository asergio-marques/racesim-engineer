#ifndef PROCESSOR_INCLUDE_FACADE_H_
#define PROCESSOR_INCLUDE_FACADE_H_

#include <memory>
#include "IFacade.h"


namespace Processor {

    namespace Data {

        class Databank;

    }

    class Facade : public Processor::IFacade {

        public:
            Facade();
            virtual ~Facade();
            virtual void OnPacketBroadcast(Packet::Game::Interface* packet) override final;

        private:
            Processor::Data::Databank* const m_databank;

    };

}

#endif // PROCESSOR_INCLUDE_FACADE_H_