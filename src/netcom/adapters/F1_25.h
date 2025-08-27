#ifndef NETCOM_ADAPTERS_INCLUDE_F1_25_H_
#define NETCOM_ADAPTERS_INCLUDE_F1_25_H_

#include <vector>
#include "adapters/Interface.h"



namespace Packet {

	namespace Game {

		class Interface;

	}

}

namespace NetCom {

	namespace Adapter {

		class F1_25 : public NetCom::Adapter::Interface {

			public:
			F1_25();
			virtual ~F1_25() = default;

			Packet::Game::Interface* ProcessDatagram(const char* datagram) override final;

		};

	}

}

#endif // NETCOM_ADAPTERS_INCLUDE_F1_25_H_