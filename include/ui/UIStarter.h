#ifndef USERINTERFACE_INCLUDE_UI_STARTER_H_
#define USERINTERFACE_INCLUDE_UI_STARTER_H_

#include <memory>
#include <QList>
#include <QThread>
#include "packets/internal/Subscriber.h"



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
    class PacketHandler;

    class UIStarter : public Packet::Internal::Subscriber {

    public:
        UIStarter();
        virtual ~UIStarter();
        void Init(int* argc, char*** argv, Presenter::ICompFacade* presenter);
        int Run();
        void OnPacketBundleBroadcast(std::vector<Packet::Internal::Interface*> packets) override final;

    private:
        void packetProcessingExec();

        QApplication* m_app;
        UserInterface::CustomMainWindow* m_window;
        UserInterface::PacketHandler* m_handler;

    };

}

#endif // USERINTERFACE_INCLUDE_UI_STARTER_H_