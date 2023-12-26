#ifndef NETCOM_ADAPTERS_INCLUDE_F123_H_
#define NETCOM_ADAPTERS_INCLUDE_F123_H_

#include "adapters/Interface.h"

namespace Packet {

    class IPacket;

    namespace Internal {

        class Generic;

    }

}

namespace NetCom {

    namespace Adapter {

        class F1_23 : public NetCom::Adapter::Interface {

            public:
            F1_23() = default;
            ~F1_23() = default;

            Packet::IPacket* ProcessDatagram(const char* datagram) override final;
            const Packet::Internal::Generic* ConvertPacket(const Packet::IPacket* packet) override final;

        };

    }

}

#endif // NETCOM_ADAPTERS_INCLUDE_F123_H_