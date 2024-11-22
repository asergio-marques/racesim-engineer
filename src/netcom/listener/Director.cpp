#include "listener/Director.h"

#include <functional>
#include "ICompFacade.h"
#include "ISettings.h"
#include "adapters/Interface.h"
#include "packets/game/Broadcaster.h"
#include "packets/game/Interface.h"
#include "listener/ISocket.h"
#include "listener/UDPSocketWin64.h"
#include "settings/Game.h"



NetCom::Listener::Director::Director() :
    Packet::Game::Broadcaster(),
    m_socket(nullptr),
    m_gameAdapter(nullptr),
    m_shutdown(false),
    m_enabled(false) {

}



NetCom::Listener::Director::~Director() {

    delete m_socket;

}



void NetCom::Listener::Director::Init(Presenter::ICompFacade* presenter) {
    
    if (presenter) {

        m_presenter = presenter;

    }

    #ifndef LINUX
        NetCom::Listener::ISocket* socket = new NetCom::Listener::UDPSocketWin64;
    #else
        Listener::ISocket* socket = new Listener::UDPSocketLinux64;
    #endif
    
    setSocket(socket);

}



bool NetCom::Listener::Director::setSocket(NetCom::Listener::ISocket* socket) {
    
    // Check validity of injected socket
    if (socket) {
        
        // Assign new socket object and attempt to set it up fully
        m_socket = socket;
        m_socket->RegisterFunction(std::bind(&NetCom::Listener::Director::OnNewDatagramAvailable, this, std::placeholders::_1, std::placeholders::_2));
        
        if (m_socket->Init() && m_presenter) {

            auto settingsPresenter = dynamic_cast<Presenter::ISettings*>(m_presenter);
            if (settingsPresenter) {

                bool ok = true;
                uint16_t port = static_cast<uint16_t>(settingsPresenter->getSettingValue(Settings::Key::SocketPort, ok));

                if (ok) {

                    if (m_socket->Bind(port)) {

                        return true;

                    }

                }

            }

        }

    }

    return false;

}


void NetCom::Listener::Director::setGameAdapter(NetCom::Adapter::Interface* gameAdapter) {
    
    if (gameAdapter) {
        
        m_gameAdapter = gameAdapter;

    }

}


void NetCom::Listener::Director::OnNewDatagramAvailable(const char* datagram, const uint16_t datagramSize) {
    
    // Forward the datagram to the game-specific packet generator, and after the packet is generated, forward it to a dispatcher/handler
    // TODO actually dispatch/handle it
    if (m_gameAdapter) {

        Packet::Game::Interface* packet = m_gameAdapter->ProcessDatagram(datagram);
        if (packet) {
        
            #ifndef NDEBUG
            //packet->Print();
            #endif // NDEBUG

            Broadcast(packet);

        }
        else {

            // TODO error logging of discarded datagram and handling

        }

    }

}