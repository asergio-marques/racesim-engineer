#ifndef NETCOM_LISTENER_INCLUDE_F123_ADAPTER_H_
#define NETCOM_LISTENER_INCLUDE_F123_ADAPTER_H_

#include "listener/IGameAdapter.h"

namespace Packet {

    class IPacket;

}

namespace Listener {

    class F123Adapter : public IGameAdapter {

        public:
        F123Adapter() = default;
        ~F123Adapter() = default;

        Packet::IPacket* ProcessDatagram(const char* datagram) override;

    };

}


#endif // NETCOM_LISTENER_INCLUDE_F123_ADAPTER_H_