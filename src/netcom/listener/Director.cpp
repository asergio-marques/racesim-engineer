#include "listener/Director.h"

#include <functional>
#include <iostream>
#include "packets/IPacket.h"
#include "listener/F123Adapter.h"
#include "listener/IGameAdapter.h"
#include "listener/ISocket.h"
#include "listener/UDPSocketWin64.h"
#include "settings/Game.h"
#include "settings/StoreFront.h"



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
    
    // Check validity of injected socket
    if (socket) {
        
        // Assign new socket object and attempt to set it up fully
        m_socket = socket;
        m_socket->RegisterFunction(std::bind(&Listener::Director::OnNewDatagramAvailable, this, std::placeholders::_1, std::placeholders::_2));
        
        if (m_socket->Init()) {

            Settings::StoreFront* settingsStore = Settings::StoreFront::getInstance();

            if (settingsStore) {

                bool ok;
                int64_t port = settingsStore->getSettingValue(Settings::Key::SocketPort, ok);

                if (ok) {

                    if (m_socket->Bind(static_cast<uint16_t>(port))) {

                        return true;

                    }

                }

            }

        }

    }

    return false;

}


void Listener::Director::OnNewDatagramAvailable(const char* datagram, const uint16_t datagramSize) {
    
    // Forward the datagram to the game-specific packet generate, and after the packet is generated, forward it to a dispatcher/handler
    // TODO actually dispatch/handle it
    if (m_gameAdapter) {

        Packet::IPacket* packet = m_gameAdapter->ProcessDatagram(datagram);
        if (packet) {
        
            #ifndef NDEBUG
            packet->Print();
            #endif // NDEBUG

            // TODO delete for now to prevent memory leak
            // delete packet;

        }
        else {

            // TODO error logging of discarded datagram and handling

        }

    }

}