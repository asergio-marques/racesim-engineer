#include "listener/Director.h"

#include <functional>
#include <iostream>
#include "listener/F123Adapter.h"
#include "listener/IGameAdapter.h"
#include "listener/ISocket.h"
#include "listener/UDPSocketWin64.h"
#include "settings/Game.h"



Listener::Director::Director() :
    m_socket(nullptr),
    m_gameAdapter(nullptr),
    m_shutdown(false) {
   
    // TODO Game is always F1 23 right now
    //if (getGame() == Settings::Game::F1_23) {
    if (true) {

        m_gameAdapter = new F123Adapter;
    
    }

}



Listener::Director::~Director() {

    delete m_socket;

}

bool Listener::Director::setSocket(Listener::ISocket* socket) {
    
    if (socket) {
        
        m_socket = socket;
        m_socket->RegisterFunction(std::bind(&Listener::Director::OnNewDatagramAvailable, this, std::placeholders::_1, std::placeholders::_2));
        
        if (m_socket->Init()) {

            // TODO hardcoded at the moment, but needs to read settings later
            if (m_socket->Bind("127.0.0.1", 12007)) {

                return true;

            }

        }

    }

    return false;

}


void Listener::Director::OnNewDatagramAvailable(const char* datagram, const uint16_t datagramSize) {
    
    if (m_gameAdapter) {

        m_gameAdapter->ProcessDatagram(datagram);
        // TODO send new packet to central processing unit

    }

}