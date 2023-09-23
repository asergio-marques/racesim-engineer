#include "UDPSocketWin64.h"

#include <chrono>
#include <cstdint>
#include <iostream>
#include <thread>
#include <WinSock2.h>

Listener::UDPSocketWin64::UDPSocketWin64() :
    Listener::SocketBase(),
    m_ipAddress(),
    m_port(),
    m_isBound(false),
    m_socketDetailsSet(false),
    m_isSocketInit(false),
    m_implData(),
    m_socket(INVALID_SOCKET),
    m_datagramBuffer(),
    m_thread() {

    // Receive implementation details
    int res = WSAStartup(MAKEWORD(2, 2), &m_implData);
    if (res == NO_ERROR) {

        m_socketDetailsSet = true;

    }

}



Listener::UDPSocketWin64::~UDPSocketWin64() {

    if (m_thread.joinable()) {
    
        m_thread.join();
    
    }

}



bool Listener::UDPSocketWin64::Init() {

    if (m_socketDetailsSet && !m_isSocketInit) {
    
        m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (m_socket != INVALID_SOCKET) {
    
            m_isSocketInit = true;
            return true;
        
        }

    }

    return false;

}



bool Listener::UDPSocketWin64::Bind(const char* ipAddress, const uint16_t port, bool rebind) {

    if (m_isBound && rebind) {

        // TODO unbind if already bound

    }
    else if (m_isBound && !rebind) {
        
        // If rebind is not allowed and this is already bound, exit the function
        return false;

    }
    if (m_socketDetailsSet && m_isSocketInit) {
        
        if (ipAddress) {

            // Maximum of 15 characters (XXX.XXX.XXX.XXX)
            strncpy(m_ipAddress, ipAddress, 15);

        }

        sockaddr_in bindDetails;
        bindDetails.sin_family = AF_INET;
        bindDetails.sin_port = htons(port);
        bindDetails.sin_addr.s_addr = inet_addr(m_ipAddress);

        if (bind(m_socket, (SOCKADDR*) &bindDetails, sizeof(bindDetails))) {

            m_isBound = false;

        }
        else {

            m_thread = std::thread(&Listener::UDPSocketWin64::Exec, this);
            m_isBound = true;

        }

    }
    
    return m_isBound;

}



void Listener::UDPSocketWin64::Exec() {

    while (m_isBound) {
        
        sockaddr_in senderDetails;
        int senderDetailsSize = 0;
        int received = recvfrom(
            m_socket,
            m_datagramBuffer,
            m_datagramBufferSize,
            0,
            (SOCKADDR*)&senderDetails,
            &senderDetailsSize);

        if (m_regFunc) {

            std::cout << "Sending to registered function" << std::endl;
            m_regFunc(m_datagramBuffer, m_datagramBufferSize);

        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));

    }

}