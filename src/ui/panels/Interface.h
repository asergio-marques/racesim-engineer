#ifndef USERINTERFACE_PANELS_INCLUDE_INTERFACE_H_
#define USERINTERFACE_PANELS_INCLUDE_INTERFACE_H_

#include <map>
#include <QWidget>
#include "core/Screen.h"
#include "widgets/base/ID.h"



namespace Packet {

    namespace Internal {

        class Interface;

    }

}

namespace UserInterface {

    class PacketHandler;

    namespace Widget {

        class Interface;
        class ImageInterface;

    }

    namespace Panel {

        class Interface : public QWidget {

            Q_OBJECT

            public:
                Interface(UserInterface::PacketHandler* handler, QWidget* parent = 0);
                virtual ~Interface() = default;
                virtual void ResizePanel(const QSize& newUsefulSize);

                // Abstract function to be overridden by child classes that orders the composing widgets to cleanup
                // Necessary to ready a panel for a new session
                virtual void Cleanup() = 0;

            protected:
                bool RegisterWidget(UserInterface::Widget::Interface* widget);
                std::map<UserInterface::Widget::ID, UserInterface::Widget::Interface*> m_widgets;

                UserInterface::Widget::ImageInterface* m_background;
                UserInterface::PacketHandler* m_handler;

        };

    }

}

#endif // USERINTERFACE_PANELS_INCLUDE_INTERFACE_H_