#ifndef NETCOM_LISTENER_INCLUDE_UDPSOCKETWIN64_H_
#define NETCOM_LISTENER_INCLUDE_UDPSOCKETWIN64_H_

#include <cstdint>
#include <thread>
#include "listener/SocketBase.h"



namespace Listener {

    class UDPSocketWin64 : public SocketBase {

        public:
        UDPSocketWin64();
        virtual ~UDPSocketWin64();
        bool Bind(const char* ip_address, const uint16_t port) override final;
        void Exec() override final;

        private:
        char m_ipAddress[19] = "";
        uint16_t m_port;
        bool m_isBound;
        std::thread m_thread;

    };

}

#endif // NETCOM_LISTENER_INCLUDE_UDPSOCKETWIN64_H_