#include "UDPSocketWin64.h"



Listener::UDPSocketWin64::UDPSocketWin64() :
    m_ipAddress(),
    m_port(),
    m_isBound(false),
    m_thread() {

    m_thread = std::thread(&Listener::UDPSocketWin64::Exec, this);

}



Listener::UDPSocketWin64::~UDPSocketWin64() {

    if (m_thread.joinable()) {
    
        m_thread.join();
    
    }

}



bool Listener::UDPSocketWin64::Bind(const char* ip_address, const uint16_t port) {

    m_isBound = true;
    return m_isBound;

}



void Listener::UDPSocketWin64::Exec() {

    while (true) {


    }

}