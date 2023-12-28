#ifndef PROCESSOR_INCLUDE_FACADE_H_
#define PROCESSOR_INCLUDE_FACADE_H_

#include <memory>
#include "IFacade.h"



namespace Processor {

    class Facade : public Processor::IFacade {

        public:
            Facade() = default;
            virtual ~Facade() = default;
            virtual void OnPacketBroadcast(Packet::Game::Interface* packet) override final;

    };

}

#endif // PROCESSOR_INCLUDE_FACADE_H_