#ifndef NETCOM_LISTENER_INCLUDE_UDPSOCKETWIN64_H_
#define NETCOM_LISTENER_INCLUDE_UDPSOCKETWIN64_H_

#include <cstdint>
#include <string>
#include <thread>
#include <WinSock2.h>
#include "listener/SocketBase.h"



namespace Listener {

    class UDPSocketWin64 : public SocketBase {

        public:
        UDPSocketWin64();
        virtual ~UDPSocketWin64();
        bool Init() override final;
        bool Bind(const uint16_t port, bool rebind = false) override final;

        private:
        // Private function to obtain the IP address of the local machine (assumes the game is running on the same machine as the app)
        const std::string getLocalIPAddress();

        // Private function to perform the socket-binding logic, success is written to m_isBound
        void doBind(const uint16_t port);

        void Exec() override final;

        // Whether the WSA system has been started up successfully
        bool m_WSAInit;

        // Whether the socket has been initialized successfully
        bool m_isSocketInit;

        // Whether the socket is bound to an IP and port
        bool m_isBound;

        // IP address to which the socket has been bound (valid only after Bind is called successfully)
        std::string m_ipAddress;

        // IP address to which the socket has been bound (valid only after Bind is called successfully)
        uint16_t m_port;

        // Structure containing information for WinSock
        WSADATA m_implData;

        // Socket descriptor
        SOCKET m_socket;

        // Buffer for the data contained in a datagram
        char m_datagramBuffer[4096];

        // Buffer size, constant for all wrappers of this class
        const static size_t m_datagramBufferSize = 4096;

        // Thread within which the listen function is always running
        std::thread m_execThread;

    };

}

#endif // NETCOM_LISTENER_INCLUDE_UDPSOCKETWIN64_H_