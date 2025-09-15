#ifndef USERINTERFACE_SCREEN_INCLUDE_INTERFACE_H_
#define USERINTERFACE_SCREEN_INCLUDE_INTERFACE_H_

#include <QWidget>
#include "core/Screen.h"
#include "settings/WindowNumber.h"




namespace Packet {

    namespace Event {

        class Interface;

    }

}

namespace UserInterface {

    class PacketHandler;

    namespace Style {

        class Interface;

    }

    namespace Panel {

        class Interface;

    }

    namespace Screen {

        class Interface : public QWidget {

            Q_OBJECT

            public:
                Interface(UserInterface::PacketHandler* handler, QWidget* parent = 0);
                virtual ~Interface() = default;
                virtual void Activate(const Packet::Event::Interface* startupInfo) = 0;
                virtual void Deactivate() = 0;
                virtual const UserInterface::Screen::Type Type() const = 0;
                virtual void handleResizeEvent(const QSize newUsefulSize) = 0;

            protected:
                UserInterface::PacketHandler* m_handler;
        };

    }

}

#endif // USERINTERFACE_SCREEN_INCLUDE_INTERFACE_H_