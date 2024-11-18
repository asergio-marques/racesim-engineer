#include "Facade.h"

#include "adapters/F1_23/Facade.h"
#include "adapters/F1_24/Facade.h"
#include "listener/Director.h"
#include "converter/PacketGeneralizer.h"



NetCom::Facade::Facade() :
    m_director(new NetCom::Listener::Director),
    m_packetGeneralizer(new NetCom::Converter::PacketGeneralizer),
    m_gameAdapter(nullptr),
    m_presenter(nullptr) {

    if (m_director && m_packetGeneralizer) {
    
        m_director->Subscribe(m_packetGeneralizer);
    
    }


}

NetCom::Facade::~Facade() {



}



void NetCom::Facade::Init(Presenter::ICompFacade* presenter) {

    if (presenter) {

        m_presenter = presenter;

    }

    // TODO Game is always F1 23 right now
    //if (getGame() == Settings::Game::F1_23) {
    if (true) {

        // m_gameAdapter = new NetCom::Adapter::F1_23::Facade;
        m_gameAdapter = new NetCom::Adapter::F1_24::Facade;
        if (m_gameAdapter && m_director && m_packetGeneralizer) {

            m_director->setGameAdapter(m_gameAdapter);
            m_packetGeneralizer->setGameAdapter(m_gameAdapter);
            m_director->Init(presenter);

        }

    }

}


Packet::Internal::Broadcaster* NetCom::Facade::exposeBroadcasterInterface() const {

    return m_packetGeneralizer;

}