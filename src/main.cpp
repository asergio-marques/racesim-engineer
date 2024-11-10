#include "packets/internal/Broadcaster.h"
#include "settings/StoreFront.h"
#include "netcom/Facade.h"
#include "Presenter.h"
#include "processor/FileIO.h"
#include "processor/Facade.h"
#include "ui/UIStarter.h"



int main(int argc, char* argv[]) {

    // Set up base components
    Processor::IFileIO* fileWorker = new Processor::FileIO;
    if (!fileWorker) return -1;

    IPresenter* presenter = new Presenter;
    if (!presenter) return -1;

    // Set up main components
    Settings::StoreFront* settingsStore = Settings::StoreFront::getInstance();
    if (settingsStore) settingsStore->Init(fileWorker, presenter);
    else return -1;

    NetCom::Facade* commComponent = new NetCom::Facade;
    if (commComponent) commComponent->Init();
    else return -1;

    Processor::IFacade* processor = new Processor::Facade;
    if (processor) processor->Init(fileWorker, presenter);
    if (!processor) return -1;

    UserInterface::UIStarter* starter = new UserInterface::UIStarter;
    if (starter && commComponent && processor) {
        Packet::Internal::Broadcaster* internalPacketBroadcast = commComponent->exposeBroadcasterInterface();
        starter->Init(&argc, &argv, presenter);
        internalPacketBroadcast->Subscribe(processor);
        internalPacketBroadcast->Subscribe(starter);
        processor->Subscribe(starter);
        return starter->Run();

    }
    else return -1;

}