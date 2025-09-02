#ifndef GENERALIZER_INCLUDE_FACADE_H_
#define GENERALIZER_INCLUDE_FACADE_H_

#include "IFacade.h"




namespace Generalizer {

    class Director;

    namespace Adapter {

		class Interface;

    }

    class Facade : public Generalizer::IFacade {

        public:
        Facade();
        virtual ~Facade() = default;

        Packet::Internal::Broadcaster* exposeBroadcasterInterface() override;
        void OnPacketBroadcast(Packet::Game::Interface* packet) override;

        private:
		Generalizer::Adapter::Interface* m_gameAdapter;

    };

}

#endif // GENERALIZER_INCLUDE_FACADE_H_