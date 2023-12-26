#ifndef NETCOM_LISTENER_INCLUDE_SOCKETBASE_H_
#define NETCOM_LISTENER_INCLUDE_SOCKETBASE_H_

#include <cstdint>
#include <functional>
#include "listener/ISocket.h"


namespace NetCom {

    namespace Listener {

        class SocketBase : public NetCom::Listener::ISocket {

            public:
            SocketBase();
            virtual ~SocketBase();
            bool RegisterFunction(std::function<void(const char*, const uint16_t)> f) override final;
            void DeregisterFunction() override final;

            protected:
            // Function object for the registered function, the logic is the same irrespective of socket-type
            std::function<void(const char*, const uint16_t)> m_regFunc;

        };

    }

}

#endif // NETCOM_LISTENER_INCLUDE_SOCKETBASE_H_