#include "listener/SocketBase.h"

#include <cstdint>
#include <functional>
#include "listener/ISocket.h"



NetCom::Listener::SocketBase::SocketBase() :
    Listener::ISocket(),
    m_regFunc(nullptr) {



}



NetCom::Listener::SocketBase::~SocketBase() {



}

bool NetCom::Listener::SocketBase::RegisterFunction(std::function<void(const char*, const uint16_t)> f) {
    
    // Validate function pointer received
    if (f) {

        // Always overwrite the already-existing pointer
        m_regFunc = f;
        return true;

    }

    return false;

}


void NetCom::Listener::SocketBase::DeregisterFunction() {

    m_regFunc = nullptr;

}