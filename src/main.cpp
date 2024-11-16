#include "packets/internal/Broadcaster.h"
#include "settings/StoreFront.h"
#include "netcom/Facade.h"
#include "Presenter.h"
#include "processor/Facade.h"
#include "ui/UIStarter.h"



int main(int argc, char* argv[]) {

    IPresenter* presenter = new Presenter;
    if (!presenter) return -1;

    Settings::StoreFront* settingsStore = Settings::StoreFront::getInstance();
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

        // init components in reverse order
        settingsStore->Init(presenter);
        starter->Init(&argc, &argv, presenter);
        processor->Init(presenter);
        commComponent->Init();

        return starter->Run();

    }

    else return -1;

}