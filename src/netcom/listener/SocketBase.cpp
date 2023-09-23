#include "listener/SocketBase.h"

#include <cstdint>
#include "listener/ISocket.h"



Listener::SocketBase::SocketBase() :
    Listener::ISocket(),
    m_regFunc(nullptr) {



}



Listener::SocketBase::~SocketBase() {



}

bool Listener::SocketBase::RegisterFunction(void (*f)(const char*, const uint16_t)) {
    
    if (f) {

        m_regFunc = f;
        return true;

    }

    return false;

}


void Listener::SocketBase::DeregisterFunction() {

    m_regFunc = nullptr;

}