#ifndef USERINTERFACE_SCREEN_INCLUDE_DUAL_PANEL_INTERFACE_H_
#define USERINTERFACE_SCREEN_INCLUDE_DUAL_PANEL_INTERFACE_H_

#include "screens/Interface.h"
#include "settings/WindowNumber.h"




class QResizeEvent;
class QWidget;

namespace UserInterface {

    class PacketHandler;

    namespace Style {

        class Interface;

    }

    namespace Panel {

        class Interface;

    }

    namespace Screen {

        class DualPanelInterface : public Interface {

            Q_OBJECT

            public:
                DualPanelInterface(UserInterface::PacketHandler* handler, QWidget* parent = 0);
                virtual ~DualPanelInterface() = default;
                virtual void Deactivate() override;

            public slots:
                virtual void handleResizeEvent(const QSize newUsefulSize) override final;

            protected:
                void Initialize(QSharedPointer<Packet::Event::Interface> startupInfo);
                Settings::WindowNumber m_mode;
                UserInterface::Panel::Interface* m_panelLeft;
                UserInterface::Panel::Interface* m_panelRight;

        };

    }

}

#endif // USERINTERFACE_SCREEN_INCLUDE_DUAL_PANEL_INTERFACE_H_