#ifndef USERINTERFACE_PANELS_INCLUDE_INTERFACE_H_
#define USERINTERFACE_PANELS_INCLUDE_INTERFACE_H_

#include <map>
#include <QWidget>
#include "widgets/base/ID.h"



namespace Packet {

    namespace Internal {

        class Interface;

    }

}

namespace UserInterface {

    namespace Widget {

        class Interface;
        class ImageInterface;

    }

    namespace Panel {

        class Interface : public QWidget {

            Q_OBJECT

            public:
                Interface(QWidget* parent = 0);
                virtual ~Interface() = default;
                virtual bool UpdateWidget(const UserInterface::Widget::ID& id, const Packet::Internal::Interface* dataPacket);
                virtual void ResizePanel(const QSize& newPanelSize);

            protected:
                bool RegisterWidget(UserInterface::Widget::Interface* widget);
                std::map<UserInterface::Widget::ID, UserInterface::Widget::Interface*> m_widgets;

                UserInterface::Widget::ImageInterface* m_background;

        };

    }

}

#endif // USERINTERFACE_PANELS_INCLUDE_INTERFACE_H_