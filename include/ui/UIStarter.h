#ifndef USERINTERFACE_INCLUDE_UI_STARTER_H_
#define USERINTERFACE_INCLUDE_UI_STARTER_H_

#include <memory>
#include <QList>
#include <QThread>
#include "packets/event/Subscriber.h"



class QApplication;
class QWidget;

namespace Packet {

    namespace Internal {

        class Interface;

    }
}

namespace Presenter {

    class ICompFacade;

}

namespace UserInterface {

    class CustomMainWindow;
    class EventAnnouncer;
    class PacketHandler;

    class UIStarter : public Packet::Event::Subscriber {

    public:
        UIStarter();
        virtual ~UIStarter();
        void Init(int* argc, char*** argv, Presenter::ICompFacade* presenter);
        int Run();
        void OnPacketBundleBroadcast(std::vector<Packet::Event::Interface*> packets) override final;

    private:
        void packetProcessingExec();

        QApplication* m_app;
        UserInterface::CustomMainWindow* m_window;
        UserInterface::PacketHandler* m_handler;
        UserInterface::EventAnnouncer* m_announcer;

    };

}

#endif // USERINTERFACE_INCLUDE_UI_STARTER_H_