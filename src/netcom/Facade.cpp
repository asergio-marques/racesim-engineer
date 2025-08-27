#include "Facade.h"

#include "adapters/F1_25.h"
#include "listener/Director.h"



NetCom::Facade::Facade() :
    m_director(new NetCom::Listener::Director),
    m_gameAdapter(nullptr),
    m_presenter(nullptr) {


}



NetCom::Facade::~Facade() {



}



void NetCom::Facade::Init(Presenter::ICompFacade* presenter) {

    if (!presenter) {

        return;

    }

    m_presenter = presenter;

    // TODO Game is always F1 25 right now
    //if (m_presenter->GetGame() == Settings::Game::F1_25) {
    if (true) {

        m_gameAdapter = new NetCom::Adapter::F1_25;

        if (m_gameAdapter && m_director) {

            m_director->setGameAdapter(m_gameAdapter);
            m_director->Init(presenter);

        }

    }

}


Packet::Game::Broadcaster* NetCom::Facade::exposeBroadcasterInterface() const {

    return m_director;

}