#include "packets/internal/Broadcaster.h"
#include "settings/StoreFront.h"
#include "netcom/Facade.h"
#include "processor/Facade.h"
#include "ui/UIStarter.h"



int main(int argc, char* argv[]) {

    // Set up components
    Settings::StoreFront* settingsStore = Settings::StoreFront::getInstance();
    if (settingsStore) settingsStore->Init();
    else return -1;

    NetCom::Facade* commComponent = new NetCom::Facade;
    if (commComponent) commComponent->Init();
    else return -1;

    Processor::IFacade* processor = new Processor::Facade;
    if (!processor) return -1;

    /*Packet::Subscriber* presenter = new Presenter::Presenter;
    if (presenter) {

        director->Subscribe(presenter);
        processor->Subscribe(presenter);

    }
    else return -1;*/

    UserInterface::UIStarter* starter = new UserInterface::UIStarter;
    if (starter && commComponent && processor) {
        Packet::Internal::Broadcaster* internalPacketBroadcast = commComponent->exposeBroadcasterInterface();
        starter->Init(&argc, &argv);
        internalPacketBroadcast->Subscribe(processor);
        internalPacketBroadcast->Subscribe(starter);
        processor->Subscribe(starter);
        return starter->Run();

    }
    else return -1;

}