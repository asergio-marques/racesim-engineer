#ifndef NETCOM_LISTENER_INCLUDE_SOCKETBASE_H_
#define NETCOM_LISTENER_INCLUDE_SOCKETBASE_H_

#include <cstdint>
#include "listener/ISocket.h"


namespace Listener {

    class SocketBase : public ISocket {

        public:
        SocketBase();
        virtual ~SocketBase();
        bool RegisterFunction(void (*f)(const char*, const uint16_t)) override final;
        void DeregisterFunction() override final;

        protected:
        void (*m_regFunc)(const char*, uint16_t);

    };

}

#endif // NETCOM_LISTENER_INCLUDE_SOCKETBASE_H_