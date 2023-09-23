#ifndef NETCOM_LISTENER_INCLUDE_UDPSOCKETWIN64_H_
#define NETCOM_LISTENER_INCLUDE_UDPSOCKETWIN64_H_

#include <cstdint>
#include <thread>
#include <WinSock2.h>
#include "listener/SocketBase.h"



namespace Listener {

    class UDPSocketWin64 : public SocketBase {

        public:
        UDPSocketWin64();
        virtual ~UDPSocketWin64();
        bool Init() override final;
        bool Bind(const char* ipAddress, const uint16_t port, bool rebind = false) override final;
        void Exec() override final;

        private:
        char m_ipAddress[15] = "";
        uint16_t m_port;
        bool m_isBound;
        bool m_socketDetailsSet;
        bool m_isSocketInit;
        WSADATA m_implData;
        SOCKET m_socket;
        char m_datagramBuffer[4096];
        const static size_t m_datagramBufferSize = 4096;
        std::thread m_thread;

    };

}

#endif // NETCOM_LISTENER_INCLUDE_UDPSOCKETWIN64_H_