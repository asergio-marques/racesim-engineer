#include "listener/SocketBase.h"

#include <cstdint>
#include <functional>
#include "listener/ISocket.h"



Listener::SocketBase::SocketBase() :
    Listener::ISocket(),
    m_regFunc(nullptr) {



}



Listener::SocketBase::~SocketBase() {



}

bool Listener::SocketBase::RegisterFunction(std::function<void(const char*, const uint16_t)> f) {
    
    // Validate function pointer received
    if (f) {

        // Always overwrite the already-existing pointer
        m_regFunc = f;
        return true;

    }

    return false;

}


void Listener::SocketBase::DeregisterFunction() {

    m_regFunc = nullptr;

}