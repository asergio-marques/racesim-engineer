#ifndef NETCOM_ADAPTERS_INCLUDE_F123_H_
#define NETCOM_ADAPTERS_INCLUDE_F123_H_

#include "adapters/Interface.h"

namespace Packet {

    namespace Game {

        class Interface;

    }

    namespace Internal {

        class Interface;

    }

}

namespace NetCom {

    namespace Adapter {

        class F1_23 : public NetCom::Adapter::Interface {

            public:
            F1_23() = default;
            ~F1_23() = default;

            Packet::Game::Interface* ProcessDatagram(const char* datagram) override final;
            const Packet::Internal::Interface* ConvertPacket(const Packet::Game::Interface* packet) override final;

        };

    }

}

#endif // NETCOM_ADAPTERS_INCLUDE_F123_H_