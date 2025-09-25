#ifndef USERINTERFACE_SCREEN_INCLUDE_SINGLE_PANEL_INTERFACE_H_
#define USERINTERFACE_SCREEN_INCLUDE_SINGLE_PANEL_INTERFACE_H_

#include <QSharedPointer>
#include <QWidget>
#include "screens/Interface.h"
#include "settings/WindowNumber.h"




namespace UserInterface {

    class PacketHandler;

    namespace Style {

        class Interface;

    }

    namespace Panel {

        class Interface;

    }

    namespace Screen {

        class SinglePanelInterface : public Interface {

            Q_OBJECT

            public:
                SinglePanelInterface(UserInterface::PacketHandler* handler, QWidget* parent = 0);
                virtual ~SinglePanelInterface() = default;
                virtual void Deactivate() override;

            public slots:
                virtual void handleResizeEvent(const QSize newUsefulSize) override final;

            protected:
                void Initialize(QSharedPointer<Packet::Event::Interface> startupInfo);
                Settings::WindowNumber m_mode;
                UserInterface::Panel::Interface* m_panel;

        };

    }

}

#endif // USERINTERFACE_SCREEN_INCLUDE_SINGLE_PANEL_INTERFACE_H_