#include "generalizer/Facade.h"
#include "packets/game/Broadcaster.h"
#include "packets/internal/Broadcaster.h"
#include "presenter/Presenter.h"
#include "processor/Facade.h"
#include "netcom/Facade.h"
#include "settings/Store.h"
#include "ui/UIStarter.h"



int main(int argc, char* argv[]) {

    Presenter::ICompFacade* presenter = new Presenter::Facade;
    if (!presenter) return -1;

    Settings::IStore* settingsStore = new Settings::Store;
    if (!settingsStore) return -1;

    NetCom::Facade* commComponent = new NetCom::Facade;
    if (!commComponent) return -1;

    Processor::IFacade* processor = new Processor::Facade;
    if (!processor) return -1;

    Generalizer::IFacade* generalizer = new Generalizer::Facade;
	if (!generalizer) return -1;

    UserInterface::UIStarter* starter = new UserInterface::UIStarter;
    if (!starter) return -1;

    if (presenter && commComponent && processor && starter) {

        // subscribe to packet broadcasters
        // the netcom component only convert byte data to game packets, sending them to the generalizer
        Packet::Game::Broadcaster* gameBroadcast = commComponent->exposeBroadcasterInterface();
        gameBroadcast->Subscribe(generalizer);

        // the generalizer component only converts game packets to internal packets, sending them to the processor
		Packet::Internal::Broadcaster* internalBroadcast = generalizer->exposeBroadcasterInterface();
        internalBroadcast->Subscribe(processor);

        // the processor component processes internal packets and converts them to event packets, sending them to the UI
		Packet::Event::Broadcaster* eventBroadcast = processor->exposeBroadcasterInterface();
        eventBroadcast->Subscribe(starter);

        // init components
        settingsStore->Init(presenter);
        starter->Init(&argc, &argv, presenter);
        processor->Init(presenter);
        commComponent->Init(presenter);

        return starter->Run();

    }

    else return -1;

}