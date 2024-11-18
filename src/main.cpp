#include "packets/internal/Broadcaster.h"
#include "presenter/Presenter.h"
#include "processor/Facade.h"
#include "netcom/Facade.h"
#include "settings/StoreFront.h"
#include "ui/UIStarter.h"



int main(int argc, char* argv[]) {

    Presenter::ICompFacade* presenter = new Presenter::Facade;
    if (!presenter) return -1;

    Settings::StoreFront* settingsStore = new Settings::StoreFront;
    if (!settingsStore) return -1;

    NetCom::Facade* commComponent = new NetCom::Facade;
    if (!commComponent) return -1;

    Processor::IFacade* processor = new Processor::Facade;
    if (!processor) return -1;

    UserInterface::UIStarter* starter = new UserInterface::UIStarter;
    if (!starter) return -1;

    if (presenter && commComponent && processor && starter) {

        // subscribe to packet broadcasters
        Packet::Internal::Broadcaster* internalPacketBroadcast = commComponent->exposeBroadcasterInterface();
        internalPacketBroadcast->Subscribe(processor);
        internalPacketBroadcast->Subscribe(starter);
        processor->Subscribe(starter);

        // init components
        settingsStore->Init(presenter);
        starter->Init(&argc, &argv, presenter);
        processor->Init(presenter);
        commComponent->Init();

        return starter->Run();

    }

    else return -1;

}